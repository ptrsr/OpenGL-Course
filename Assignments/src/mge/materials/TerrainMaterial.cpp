#include <glm.hpp>

#include "mge/materials/TerrainMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"



TerrainMaterial::TerrainMaterial(std::string pHeight, std::string pDifR, std::string pDifG, std::string pDifB, std::string pDifA, std::string pSplat) :
	LitMaterial(Lit::splat)
{
	std::string path = config::MGE_TEXTURE_PATH + "terrain/";

	_heightMap = Texture::load(path + pHeight);
	_splatMap  = Texture::load(path + pSplat);
	_difR	   = Texture::load(path + pDifR);
	_difG	   = Texture::load(path + pDifG);
	_difB	   = Texture::load(path + pDifB);
	_difA	   = Texture::load(path + pDifA);

	_aUV = _shader->getAttribLocation("uv");
}

TerrainMaterial::~TerrainMaterial() {}

void TerrainMaterial::render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) 
{
	_shader->use();
	addLights();

	//vertex uniforms
	glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
	glUniformMatrix4fv(_uModelMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	//fragment uniforms
	glUniform3fv(_uCameraPos, 1, glm::value_ptr(((GameObject*)(World::get()->getMainCamera()))->getWorldPosition()));
	glUniform1f(_uShininess, _shininess);

	//Heightmap
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _heightMap->getId());
	glUniform1i(_shader->getUniformLocation("heightMap"), 0);

    //Diffuse R
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _difR->getId());
    glUniform1i (_shader->getUniformLocation("tDifR"), 1);

	//Diffuse G
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _difG->getId());
	glUniform1i(_shader->getUniformLocation("tDifG"), 2);

	//Diffuse B
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _difB->getId());
	glUniform1i(_shader->getUniformLocation("tDifB"), 3);

	//Diffuse A
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, _difA->getId());
	glUniform1i(_shader->getUniformLocation("tDifA"), 4);

	//Splatmap
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, _splatMap->getId());
	glUniform1i(_shader->getUniformLocation("tSplat"), 5);

	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}

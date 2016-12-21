#include "mge/materials/LitMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"

ShaderProgram* LitMaterial::_shader = NULL;

//vertex uniforms
GLint LitMaterial::_uMVPMatrix = 0;
GLint LitMaterial::_uModelMatrix = 0;
GLint LitMaterial::_uLightDirection = 0;

//vertex attributes
GLint LitMaterial::_aVertex = 0;
GLint LitMaterial::_aNormal = 0;

//fragment uniforms
GLint LitMaterial::_uAmbientColor = 0;
GLint LitMaterial::_uDiffuseColor = 0;
GLint LitMaterial::_uDiLightColor = 0;


LitMaterial::LitMaterial(std::vector<DirectionalLight*>* pLights, glm::vec3 pDiffuseColor, glm::vec3 pDirection) :
	_diffuseColor(pDiffuseColor),
	_Lights(pLights),
	_lightDirection(pDirection)
{
	_lazyInitializeShader();

	_ambientColor = glm::vec3(1, 1, 1) * 0.1f;
	_diLightColor = glm::vec3(1, 1, 1);

	_lightDirection = glm::vec3(-1, -1, -1);
}

LitMaterial::~LitMaterial() {}

void LitMaterial::_lazyInitializeShader() 
{
	if (!_shader) 
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "litFragment.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "litFragment.fs");
		_shader->finalize();

		//vertex uniforms
		_uMVPMatrix		 = _shader->getUniformLocation("mvpMatrix");
		_uModelMatrix    = _shader->getUniformLocation("modelMatrix");
		_uLightDirection = _shader->getUniformLocation("diLightDir");

		//vertex attributes
		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");

		//fragment uniforms
		_uAmbientColor = _shader->getUniformLocation("ambientColor");
		_uDiffuseColor = _shader->getUniformLocation("diffuseColor");
		_uDiLightColor = _shader->getUniformLocation("diLightColor");
	}
}

void LitMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
	_diffuseColor = pDiffuseColor;
}

void LitMaterial::render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	_shader->use();

	//vertex uniforms
	glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
	glUniformMatrix4fv(_uModelMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	glUniform3fv(_uLightDirection, 1, glm::value_ptr(glm::normalize(_lightDirection)));

	//vertex attributes
	pMesh->streamToOpenGL(_aVertex, _aNormal, -1);

	//fragment uniforms
	glUniform3fv(_uAmbientColor, 1, glm::value_ptr(_ambientColor));
	glUniform3fv(_uDiffuseColor, 1, glm::value_ptr(_diffuseColor));
	glUniform3fv(_uDiLightColor, 1, glm::value_ptr(_diLightColor));
}


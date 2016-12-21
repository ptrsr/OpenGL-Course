#include <glm.hpp>

#include "mge/materials/WobbleMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"


ShaderProgram* WobbleMaterial::_shader = NULL;

WobbleMaterial::WobbleMaterial(Texture * pDiffuseTexture, Mesh * pMesh) :_diffuseTexture(pDiffuseTexture) 
{
	timer = new sf::Clock();
	_lazyInitializeShader();

	//wobble
	int vertexCount = pMesh->VertexCount();
	GLint * phase = new GLint[vertexCount - 1];

	for (int i = 0; i < vertexCount; i++)
		phase[i] = i;

	GLuint phaseBufferId;
	glGenBuffers(1, &phaseBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, phaseBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(phase) * vertexCount, phase, GL_STATIC_DRAW);

	GLint phaseIndex = _shader->getAttribLocation("phase");

	glEnableVertexAttribArray(phaseIndex);
	glVertexAttribIPointer(phaseIndex, 1, GL_INT, GL_FALSE, 0);
}

WobbleMaterial::~WobbleMaterial() {}

void WobbleMaterial::_lazyInitializeShader() {
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "wobble.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "texture.fs");
		_shader->finalize();
	}
}

void WobbleMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
	_diffuseTexture = pDiffuseTexture;
}

void WobbleMaterial::render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (!_diffuseTexture) return;

	_shader->use();

	glUniform1i(_shader->getUniformLocation("phases"), pMesh->VertexCount());
	glUniform1f(_shader->getUniformLocation("clock"), timer->getElapsedTime().asSeconds());

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
	glUniform1i(_shader->getUniformLocation("textureDiffuse"), 0);

	//pass in all MVP matrices separately
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	
	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		_shader->getAttribLocation("normal"),
		_shader->getAttribLocation("uv")
	);


	//glDisableVertexAttribArray(phaseIndex);
}

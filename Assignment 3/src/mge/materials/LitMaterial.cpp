#include "mge/materials/LitMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"
#include <string>

ShaderProgram* LitMaterial::_shader = NULL;

//vertex uniforms
GLint LitMaterial::_uMVPMatrix = 0;
GLint LitMaterial::_uModelMatrix = 0;

//fragment uniforms
GLint LitMaterial::_uModelColor = 0;
GLint LitMaterial::_uShininess = 0;
GLint LitMaterial::_uCameraPos = 0;

//vertex attributes
GLint LitMaterial::_aVertex = 0;
GLint LitMaterial::_aNormal = 0;


LitMaterial::LitMaterial(std::vector<AbstractLight*>* pLights) : _lights(pLights)
{
	_lazyInitializeShader();
	_modelColor = glm::vec3(1, 1, 1);
	_shininess = 10.0f;
}

LitMaterial::~LitMaterial() {}

void LitMaterial::_lazyInitializeShader() 
{
	if (!_shader) 
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "litFragment2.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "litFragment2.fs");
		_shader->finalize();

		//vertex uniforms
		_uMVPMatrix		 = _shader->getUniformLocation("mvpMatrix");
		_uModelMatrix    = _shader->getUniformLocation("modelMatrix");

		//fragment uniforms
		_uModelColor = _shader->getUniformLocation("modelColor");
		_uShininess  = _shader->getUniformLocation("shininess");
		_uCameraPos  = _shader->getUniformLocation("cameraPos");

		//vertex attributes
		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
	}
}

void LitMaterial::render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) 
{
	_shader->use();
	addLights();

	//vertex uniforms
	glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
	glUniformMatrix4fv(_uModelMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	//fragment uniforms
	glUniform3fv(_uModelColor, 1, glm::value_ptr(_modelColor));
	glUniform3fv(_uCameraPos, 1, glm::value_ptr(((GameObject*)(World::get()->getMainCamera()))->getWorldPosition()));
	glUniform1f(_uShininess, _shininess);

	//vertex attributes
	pMesh->streamToOpenGL(_aVertex, _aNormal, -1);

	//pMesh->drawDebugInfo(pModelMatrix, pViewMatrix, pProjectionMatrix);
}

void LitMaterial::addLights()
{
	
	int dLights;
	for each (AbstractLight* light in *_lights)
	{
		if (typeid(*light) == typeid(DirectionalLight))
		{
			string num = std::to_string(dLights);
			DirectionalLight* nLight = static_cast<DirectionalLight*>(light);

			glUniform3fv(_shader->getUniformLocation("dirLight[" + num + "].direction"), 1, glm::value_ptr(nLight->_direction));
			glUniform3fv(_shader->getUniformLocation("dirLight[" + num + "].ambient"), 1, glm::value_ptr(nLight->_ambient));
			glUniform3fv(_shader->getUniformLocation("dirLight[" + num + "].diffuse"), 1, glm::value_ptr(nLight->_diffuse));
			glUniform3fv(_shader->getUniformLocation("dirLight[" + num + "].specular"), 1, glm::value_ptr(nLight->_specular));
			dLights++;
		}
	}
}
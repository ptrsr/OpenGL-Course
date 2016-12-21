#ifndef LITMATERIAL_H
#define LITMATERIAL_H

#include <vector>
#include <glm.hpp>

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/ShaderProgram.hpp"

#include "mge/behaviours/DirectionalLight.hpp"

class LitMaterial : public AbstractMaterial
{
public:
	LitMaterial(std::vector<DirectionalLight*>* pLights, glm::vec3 pColor = glm::vec3(1, 0, 0), glm::vec3 pDirection = glm::vec3(0, -1, 0));
	virtual ~LitMaterial();

	virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	void setDiffuseColor(glm::vec3 pDiffuseColor);

protected:
private:
	glm::vec3 _lightDirection;

	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//vertex uniforms
	static GLint _uMVPMatrix;
	static GLint _uModelMatrix;
	static GLint _uLightDirection;

	//vertex attributes
	static GLint _aVertex;
	static GLint _aNormal;

	//fragment uniforms
	static GLint _uAmbientColor;
	static GLint _uDiffuseColor;
	static GLint _uDiLightColor;

	std::vector<DirectionalLight*>* _Lights;

	glm::vec3 _diffuseColor;
	glm::vec3 _ambientColor;
	glm::vec3 _diLightColor;

	LitMaterial(const LitMaterial&);
	LitMaterial& operator=(const LitMaterial&);

};

#endif // LITMATERIAL_H

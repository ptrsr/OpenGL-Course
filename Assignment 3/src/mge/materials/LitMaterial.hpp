#ifndef LITMATERIAL_H
#define LITMATERIAL_H

#include <vector>
#include <glm.hpp>

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/behaviours/DirectionalLight.hpp"
#include "mge/core/World.hpp"

class LitMaterial : public AbstractMaterial
{
public:
	LitMaterial(std::vector<AbstractLight*>* pLights);
	virtual ~LitMaterial();

	virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//vertex uniforms
	static GLint _uMVPMatrix;
	static GLint _uModelMatrix;

	//vertex attributes
	static GLint _aVertex;
	static GLint _aNormal;

	//fragment uniforms
	static GLint _uModelColor;
	static GLint _uShininess;
	static GLint _uCameraPos;

	std::vector<AbstractLight*>* _lights;
	glm::vec3 _modelColor;
	float _shininess;

	LitMaterial(const LitMaterial&);
	LitMaterial& operator=(const LitMaterial&);

	void addLights();
};

#endif // LITMATERIAL_H

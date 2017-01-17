#ifndef LITMATERIAL_H
#define LITMATERIAL_H

#include <vector>
#include <glm.hpp>

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/behaviours/AbstractLight.hpp"
#include "mge/core/World.hpp"

class LitMaterial : public AbstractMaterial
{
public:
	enum Lit
	{
		fragment,
		vertex
	};

	LitMaterial(Lit pLit = vertex, glm::vec3 pModelColor = glm::vec3(1), float pShininess = 10.0f, std::vector<AbstractLight*>* pLights = World::get()->GetLights());
	virtual ~LitMaterial();

	virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

private:

	std::vector<AbstractLight*>* _lights;
	glm::vec3 _modelColor;
	float _shininess;
	
	static Lit _lit;

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

	LitMaterial(const LitMaterial&);

	void addLights();
};

#endif // LITMATERIAL_H

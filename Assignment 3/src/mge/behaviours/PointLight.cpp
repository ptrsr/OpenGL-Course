#include "DirectionalLight.hpp"



DirectionalLight::DirectionalLight(glm::vec3 pDirection, glm::vec3 pDiffuse, glm::vec3 pAmbient)
{
	_direction = glm::normalize(pDirection);
	_diffuse = pDiffuse;
	_ambient = pAmbient;
}


DirectionalLight::~DirectionalLight()
{
}

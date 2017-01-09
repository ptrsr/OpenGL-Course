#ifndef DIRECTIONALLIGHT
#define DIRECTIONALLIGHT

#include "mge\behaviours\AbstractLight.hpp"
#include <glm.hpp>

class DirectionalLight : public AbstractLight
{
public:
	void virtual update() { };

	glm::vec3 _direction;

	DirectionalLight(glm::vec3 pDirection = glm::vec3(0, -1, 0), glm::vec3 pDiffuse = glm::vec3(1, 1, 1), glm::vec3 pAmbient = glm::vec3(0.1f, 0.1f, 0.1f));
	~DirectionalLight();
};

#endif // !DIRECTIONALLIGHT
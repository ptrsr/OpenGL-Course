#ifndef ABSTRACTLIGHT_H
#define ABSTRACTLIGHT_H

#include "mge\behaviours\AbstractBehaviour.hpp"
#include <glm.hpp>

class AbstractLight : public AbstractBehaviour
{
public:
	AbstractLight() { };

	virtual void update(float pStep) { };

	glm::vec3 _diffuse;
	glm::vec3 _ambient;
	glm::vec3 _specular;

protected:
private:

};

#endif // !ABSTRACTLIGHT_H
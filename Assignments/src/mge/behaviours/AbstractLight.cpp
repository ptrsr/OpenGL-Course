#include "AbstractLight.hpp"
#include "mge/core/World.hpp"


AbstractLight::AbstractLight()
{
	World::get()->addLight(this);
	std::cout << "light spawned" << std::endl;
}

AbstractLight::~AbstractLight()
{
	World::get()->removeLight(this);
}

glm::vec3 AbstractLight::getWorldPosition()
{
	return _owner->getWorldPosition();
}

glm::vec3 AbstractLight::getDirection()
{
	return glm::normalize(_owner->getWorldTransform()[2]);
}
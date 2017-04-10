#include "AbstractLight.hpp"
#include "mge/core/World.hpp"


AbstractLight::AbstractLight() 
{ 
	World::get()->addLight(this);
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

void AbstractLight::message(msg::Message message)
{
	switch (message)
	{
	case msg::addedToScene:
		World::get()->addLight(this);
		break;

	case msg::removedFromScene:
		World::get()->removeLight(this);
		break;
	}
}
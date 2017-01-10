#include "AbstractLight.hpp"
#include "mge/core/World.hpp"


AbstractLight::AbstractLight()
{
	World::get()->addLight(this);
	std::cout << "light spawned" << std::endl;
}
#include "mge/core/World.hpp"

using namespace std;

World* World::world;

World::World():GameObject("root"), _mainCamera(0)
{
	_lights = new std::vector<AbstractLight*>();
}

World* World::get()
{
	if (world == nullptr)
		world = new World();

	return world;
}

void World::add(GameObject* pChild)
{
	pChild->setParent(this);

	AbstractBehaviour* behaviour = pChild->getBehaviour();

	if (behaviour != nullptr && dynamic_cast<AbstractLight*>(behaviour))
		_lights->push_back((AbstractLight*)behaviour);
}

void World::setMainCamera (Camera* pCamera) {
    if (pCamera != NULL) _mainCamera = pCamera;
}

Camera* World::getMainCamera () {
    return world->_mainCamera;
}

std::vector<AbstractLight*>* World::GetLights() {
	return _lights;
}
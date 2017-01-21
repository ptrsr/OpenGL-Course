#include "mge/core/World.hpp"
#include <algorithm>

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

void World::addChild(GameObject* pChild)
{
	pChild->setParent(World::get());
}

void World::addLight(AbstractLight* pLight)
{
	_lights->push_back(pLight);
}

void World::removeLight(AbstractLight* pLight)
{
	_lights->erase(std::remove(_lights->begin(), _lights->end(), pLight), _lights->end());
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
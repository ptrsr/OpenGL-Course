#include "mge/core/World.hpp"

using namespace std;

World::World():GameObject("root"), _mainCamera(0)
{
	_lights = new std::vector<DirectionalLight*>();
}

void World::add(GameObject* pChild)
{
	pChild->setParent(this);

	AbstractBehaviour* behaviour = pChild->getBehaviour();
	
	if (behaviour != nullptr && typeid(*behaviour) == typeid(DirectionalLight))
		_lights->push_back((DirectionalLight*)behaviour);
}

void World::setMainCamera (Camera* pCamera) {
    if (pCamera != NULL) _mainCamera = pCamera;
}

Camera* World::getMainCamera () {
    return _mainCamera;
}

std::vector<DirectionalLight*>* World::GetLights() {
	return _lights;
}
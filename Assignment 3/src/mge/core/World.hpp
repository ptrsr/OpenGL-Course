#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "mge/core/GameObject.hpp"
#include "mge/behaviours/DirectionalLight.hpp"

class Camera;

class World : public GameObject
{
	public:
        World();

		void setMainCamera (Camera* pCamera);

		Camera* getMainCamera();
		std::vector<DirectionalLight*>* GetLights();

		void add(GameObject* pChild);

	private:
	    Camera* _mainCamera;
		std::vector<DirectionalLight*>* _lights;

        World(const World&);
        World& operator=(const World&);
};


#endif // WORLD_H

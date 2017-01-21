#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "mge/core/GameObject.hpp"
#include "mge/behaviours/DirectionalLight.hpp"

class Camera;

class World : public GameObject
{
	public:
		void setMainCamera (Camera* pCamera);

		static World* get();

		static Camera* getMainCamera();

		std::vector<AbstractLight*>* GetLights();

		static void addChild(GameObject*);

		void addLight(AbstractLight*);
		void removeLight(AbstractLight*);

	private:
		World();

		static World * world;

	    Camera* _mainCamera;
		std::vector<AbstractLight*>* _lights;

        World(const World&) = delete;
        World& operator=(const World&) = delete;
};


#endif // WORLD_H

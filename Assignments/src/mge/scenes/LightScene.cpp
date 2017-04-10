#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"
#include "mge/auxiliary/InputHandler.h"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/WobbleMaterial.hpp"
#include "mge/materials//LitMaterial.hpp"
#include "mge/materials/TerrainMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"
#include "mge/behaviours/OrbitBehaviour.hpp"

#include "mge/behaviours/DirectionalLight.hpp"
#include "mge/behaviours/PointLight.hpp"
#include "mge/behaviours/SpotLight.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/scenes/LightScene.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
LightScene::LightScene():AbstractGame (),_hud(0)
{
}

void LightScene::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void LightScene::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

    Camera* camera = new Camera ("camera", glm::vec3(0,0,0));
    _world->add(camera);
    _world->setMainCamera(camera);



	///SUZANA
	GameObject* suzana = new GameObject("suzana", glm::vec3(0, 1.f, 0));
	suzana->setMesh(Mesh::load(config::MGE_MODEL_PATH + "suzanna_smooth.obj", 0.5f));
	suzana->setMaterial(new LitMaterial(LitMaterial::Lit::fragment, glm::vec3(1), 40.0f));
	_world->add(suzana);


	///CAMERA
	GameObject* empty = new GameObject("empty", glm::vec3(0, 1, 0));
	camera->setBehaviour(new OrbitBehaviour(empty, 3));

	///POINT LIGHT
	glm::vec3 pointColor = glm::vec3(1, 0, 0);

	rotor1 = new GameObject("rotor", glm::vec3(0, 1.5f, 0));
	GameObject* point = new GameObject("point");
	rotor1->setBehaviour(new RotatingBehaviour());
	point->setParent(rotor1);
	_world->add(rotor1);

	point->setMesh(Mesh::load(config::MGE_MODEL_PATH + "sphere_flat.obj", 0.1f));
	point->setMaterial(new ColorMaterial(pointColor));
	point->setBehaviour(new PointLight(pointColor, glm::vec3(0.1f), glm::vec3(1), 0.4f, 0.5f, 0.7f));
	point->translate(glm::vec3(0, 0, 1));

	///POINT LIGHT 2
	glm::vec3 pointColor2 = glm::vec3(0, 0, 1);

	rotor2 = new GameObject("rotor2", glm::vec3(0, 1.5f, 0.3f));
	GameObject* point2 = new GameObject("point2");
	rotor2->setBehaviour(new RotatingBehaviour());
	point2->setParent(rotor2);
	_world->add(rotor2);

	point2->setMesh(Mesh::load(config::MGE_MODEL_PATH + "sphere_flat.obj", 0.1f));
	point2->setMaterial(new ColorMaterial(pointColor2));
	point2->setBehaviour(new PointLight(pointColor2, glm::vec3(0.1f), glm::vec3(1), 0.4f, 0.5f, 0.7f));
	point2->translate(glm::vec3(0, 0, -1));
	rotor2->rotate(180.0f, glm::vec3(1, 0, 0));
}

void LightScene::_render() 
{
	if (InputHandler::GetKeyDown(sf::Keyboard::Num1))
	{
		if (rotor1->getParent() == NULL)
			rotor1->setParent(_world);
		else
			rotor1->setParent(NULL);
	}

	if (InputHandler::GetKeyDown(sf::Keyboard::Num2))
	{
		if (rotor2->getParent() == NULL)
			rotor2->setParent(_world);
		else
			rotor2->setParent(NULL);
	}

    AbstractGame::_render();
    _updateHud();
}

void LightScene::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

LightScene::~LightScene()
{
	//dtor
}

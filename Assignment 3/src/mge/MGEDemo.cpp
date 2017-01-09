#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/WobbleMaterial.hpp"
#include "mge/materials//LitMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"
#include "mge/behaviours/OrbitBehaviour.hpp"
#include "mge/behaviours/DirectionalLight.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame (),_hud(0)
{
}

void MGEDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void MGEDemo::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

    //add camera first (it will be updated last)
    Camera* camera = new Camera ("camera", glm::vec3(0,0,0));
    _world->add(camera);
    _world->setMainCamera(camera);

    ///PLANE
 //   GameObject* plane = new GameObject ("plane", glm::vec3(0,0,0));
	//
	//Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	//plane->setMesh(planeMesh);
	//plane->scale(glm::vec3(5,5,5));

	//AbstractMaterial* planeMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));
 //   plane->setMaterial(planeMaterial);

 //   _world->add(plane);

	///LIGHTS
	GameObject* lightSource = new GameObject("lightSource");
	lightSource->setBehaviour(new DirectionalLight(glm::vec3(-1, -1, -1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 0)));
	_world->add(lightSource);

	GameObject* lightSource2 = new GameObject("lightSource2");
	lightSource2->setBehaviour(new DirectionalLight(glm::vec3(1, 1, 1), glm::vec3(1,0,0), glm::vec3(0,0,0)));
	_world->add(lightSource2);

	///LUCAS
    GameObject* lucas = new GameObject ("Lucas", glm::vec3(0, 0, 0));

	Mesh* ballMesh = Mesh::load(config::MGE_MODEL_PATH + "lucas.obj", 0.0013f);
    lucas->setMesh(ballMesh);

	AbstractMaterial* lucasMaterial = new LitMaterial(_world->GetLights());
    lucas->setMaterial(lucasMaterial);

    _world->add(lucas);

	///CAMERA
	GameObject* empty = new GameObject("empty", glm::vec3(0, 1, 0));
	camera->setBehaviour(new OrbitBehaviour(_window, empty, 3));
}

void MGEDemo::_render() {
    AbstractGame::_render();
    _updateHud();
}

void MGEDemo::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

MGEDemo::~MGEDemo()
{
	//dtor
}

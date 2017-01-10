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
#include "mge/behaviours/PointLight.hpp"
#include "mge/behaviours/SpotLight.hpp"

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

    Camera* camera = new Camera ("camera", glm::vec3(0,0,0));
    _world->addChild(camera);
    _world->setMainCamera(camera);

    ///PLANE
    //GameObject* plane = new GameObject ("plane", glm::vec3(0,0,0));
	//Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	//plane->setMesh(planeMesh);
	//plane->scale(glm::vec3(5,5,5));
    //plane->setMaterial(new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));
    //_world->add(plane);

	///RED DIR
	//GameObject* lightSource = new GameObject("lightSource");
	//lightSource->setBehaviour(new DirectionalLight(glm::vec3(-1, -1, -1), glm::vec3(0, 0, 1), glm::vec3(0.1f)));
	//_world->addChild(lightSource);

	///BLUE DIR
	//GameObject* lightSource2 = new GameObject("lightSource2");
	//lightSource2->setBehaviour(new DirectionalLight(glm::vec3(1, 1, 1), glm::vec3(1,0,0), glm::vec3(0,0,0)));
	//_world->addChild(lightSource2);

	///POINT LIGHT
	//glm::vec3 pointColor = glm::vec3(1, 0, 0);
	//
	//GameObject* rotor = new GameObject("rotor", glm::vec3(0, 1, 0));
	//GameObject* point = new GameObject("point");
	//rotor->setBehaviour(new RotatingBehaviour());
	//point->setParent(rotor);
	//_world->addChild(rotor);

	//point->setMesh(Mesh::load(config::MGE_MODEL_PATH + "sphere_flat.obj", 0.1f));
	//point->setMaterial(new ColorMaterial(pointColor));
	//point->setBehaviour(new PointLight(pointColor, glm::vec3(0.1f), glm::vec3(1), 0.4f, 0.5f, 0.7f));
	//point->translate(glm::vec3(0, 0, 1));

	///POINT LIGHT 2
	//glm::vec3 pointColor2 = glm::vec3(0, 0, 1);

	//GameObject* rotor2 = new GameObject("rotor2", glm::vec3(0, 1, 0));
	//GameObject* point2 = new GameObject("point2");
	//rotor2->setBehaviour(new RotatingBehaviour());
	//point2->setParent(rotor2);
	//_world->addChild(rotor2);

	//point2->setMesh(Mesh::load(config::MGE_MODEL_PATH + "sphere_flat.obj", 0.1f));
	//point2->setMaterial(new ColorMaterial(pointColor2));
	//point2->setBehaviour(new PointLight(pointColor2, glm::vec3(0.1f), glm::vec3(1), 0.4f, 0.5f, 0.7f));
	//point2->translate(glm::vec3(0, 0, 1));
	//rotor2->rotate(180.0f, glm::vec3(1, 0, 0));

	///SPOT LIGHT
	glm::vec3 spotColor = glm::vec3(1);

	GameObject * spotRotor = new GameObject("spotrotor");
	spotRotor->setBehaviour(new RotatingBehaviour());
	_world->addChild(spotRotor);

	GameObject * spotLight = new GameObject("spotLight", glm::vec3(0, 0, -1));
	spotLight->setBehaviour(new SpotLight(spotColor, spotColor, glm::vec3(1), 0.5f, 0.4f, 0.6f, 1.0f, 1.2f));
	spotLight->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cone_flat.obj"));
	spotLight->setMaterial(new ColorMaterial(spotColor));
	spotLight->setParent(spotRotor);

	///LUCAS
    GameObject* lucas = new GameObject ("Lucas", glm::vec3(0, 0, 0));
    lucas->setMesh(Mesh::load(config::MGE_MODEL_PATH + "lucas.obj", 0.0013f));
    lucas->setMaterial(new LitMaterial(_world->GetLights()));
    _world->addChild(lucas);

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

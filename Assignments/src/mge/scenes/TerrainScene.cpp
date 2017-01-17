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
#include "mge/scenes/TerrainScene.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
TerrainScene::TerrainScene():AbstractGame (),_hud(0)
{
}

void TerrainScene::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void TerrainScene::_initializeScene()
{
	_renderer->setClearColor(0, 0, 0);

	Camera* camera = new Camera("camera", glm::vec3(0, 0, 0));
	_world->addChild(camera);
	_world->setMainCamera(camera);

	GameObject* terrain = new GameObject("terrain");
	terrain->setMesh(Mesh::load(config::MGE_MODEL_PATH + "plane_8192.obj"));
	terrain->setMaterial(new TerrainMaterial(Texture::load(config::MGE_TEXTURE_PATH + "/terrain/diffuse1.jpg"), 
											 Texture::load(config::MGE_TEXTURE_PATH + "/terrain/heightmap.png")));

	_world->addChild(terrain);

	camera->setBehaviour(new OrbitBehaviour(terrain, 3));
}

void TerrainScene::_render() {
    AbstractGame::_render();
    _updateHud();
}

void TerrainScene::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

TerrainScene::~TerrainScene()
{
	//dtor
}

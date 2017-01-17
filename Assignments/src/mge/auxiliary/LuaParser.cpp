#include "LuaParser.hpp"
#include "mge/core/World.hpp"
#include "SFML\Window\Mouse.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "Hex.hpp"

int createObject(lua_State * lua) 
{
	glm::vec3 position = glm::vec3(glm::vec3(lua_tonumber(lua, -7), lua_tonumber(lua, -6), lua_tonumber(lua, -5)));
	glm::vec3 scale = glm::vec3(lua_tonumber(lua, -4), lua_tonumber(lua, -3), lua_tonumber(lua, -2));

	GameObject* obj = new GameObject(lua_tostring(lua, -8), position);
	obj->scale(scale);
	obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube_unity.obj"));

	std::string hexColor = lua_tostring(lua, -1);
	glm::vec3 color = hex::HexadecimalToRGB(hexColor) / 255.0f;

	obj->setMaterial(new ColorMaterial(color));
	World::addChild(obj);

	return 0;
}

LuaParser::LuaParser(std::string fileName) 
{
    lua = luaL_newstate();
    luaL_openlibs(lua);

	lua_pushcfunction(lua, createObject);
	lua_setglobal(lua, "createObject"); 

	luaL_dofile(lua, (config::MGE_SCENE_PATH + fileName).c_str());
}

void LuaParser::update(float pStep)
{

}
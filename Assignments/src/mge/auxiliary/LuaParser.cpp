#include "LuaParser.hpp"
#include "mge/core/World.hpp"
#include "SFML\Window\Mouse.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "Hex.hpp"
#include "ObjectCache.hpp"

//creates a GameObject and adds it to the game and ObjectCache
int spawn(lua_State* lua) 
{
	GameObject* obj = new GameObject(lua_tostring(lua, -4), glm::vec3(lua_tonumber(lua, -3), lua_tonumber(lua, -2), lua_tonumber(lua, -1)));
	ObjectCache::push(obj);

	std::cout << lua_gettop(lua) << std::endl;

	return 0;
}

//checks if a GameObject exists with a particular name
int exists(lua_State* lua)
{
	if (lua_gettop(lua) == 1 && lua_isstring(lua, -1))
		lua_pushboolean(lua, ObjectCache::exists(lua_tostring(lua, -1)));
	else
	{
		std::cout << "error: 'exist' function isn't a string" << std::endl;
		lua_pushboolean(lua, false);
	}
	return 1;
}

//pushes the position of a GameObject to lua
int getPos(lua_State* lua)
{
	if (lua_gettop(lua) == 1 && lua_isstring(lua, -1))
	{
		GameObject* obj = ObjectCache::find(lua_tostring(lua, -1));

		if (obj != nullptr)
		{
			glm::vec3 pos = obj->getWorldPosition();

			lua_pushnumber(lua, pos.x);
			lua_pushnumber(lua, pos.y);
			lua_pushnumber(lua, pos.z);
		}
		else std::cout << "error getting position: object doesn't exist" << std::endl;
	}
	else std::cout << "error: 'getPos' function param isn't a string" << std::endl;

	return 3;
}

int move(lua_State* lua)
{
	if (lua_gettop(lua) == 3 && lua_isnumber(lua, -1) && lua_isnumber(lua, -2) && lua_isnumber(lua, -3))
	{
		GameObject* obj = ObjectCache::find(lua_tostring(lua, -1));

		if (obj != nullptr)
			obj->translate(glm::vec3(lua_tonumber(lua, -3), lua_tonumber(lua, -2), lua_tonumber(lua, -1)));
		else
			std::cout << "error getting position: object doesn't exist" << std::endl;
	}
	else std::cout << "error: move param isn't a number" << std::endl;

	return 0;
}

int setPos(lua_State* lua)
{
	if (lua_gettop(lua) == 3 && lua_isnumber(lua, -1) && lua_isnumber(lua, -2) && lua_isnumber(lua, -3))
	{
		GameObject* obj = ObjectCache::find(lua_tostring(lua, -1));

		if (obj != nullptr)
			obj->setLocalPosition(glm::vec3(lua_tonumber(lua, -3), lua_tonumber(lua, -2), lua_tonumber(lua, -1)));
		else
			std::cout << "error getting position: object doesn't exist" << std::endl;
	}
	else std::cout << "error: move param isn't a number" << std::endl;

	return 0;
}

int rename(lua_State* lua)
{
	if (lua_gettop(lua) == 2 && lua_isstring(lua, -1) && lua_isstring(lua, -2))
	{
		if (!ObjectCache::rename(lua_tostring(lua, -2), lua_tostring(lua, -1)))
			std::cout << "error renaming: object doesn't exist" << std::endl;
	}
	else std::cout << "error: rename param isn't a string" << std::endl;

	return 0;
}

int remove(lua_State* lua)
{
	//TODO
}

int checkCollision(lua_State* lua)
{
	//TODO
}

int message(lua_State* lua)
{
	//TODO
}

//prints a string to console
int print(lua_State* lua)
{
	if (lua_gettop(lua) == 1 && lua_isstring(lua, -1))
		std::cout << lua_tostring(lua, -1) << std::endl;
	else
		std::cout << "error: tried printing empty string" << std::endl;

	return 0;
}

LuaParser::LuaParser(std::string fileName) 
{
    lua = luaL_newstate();
    luaL_openlibs(lua);

	lua_pushcfunction(lua, spawn);
	lua_setglobal(lua, "spawn"); 

	lua_pushcfunction(lua, exists);
	lua_setglobal(lua, "exists");

	lua_pushcfunction(lua, getPos);
	lua_setglobal(lua, "getPos");

	lua_pushcfunction(lua, move);
	lua_setglobal(lua, "move");

	lua_pushcfunction(lua, setPos);
	lua_setglobal(lua, "setPos");

	lua_pushcfunction(lua, rename);
	lua_setglobal(lua, "rename");

	lua_pushcfunction(lua, print);
	lua_setglobal(lua, "print");

	lua_pushcfunction(lua, getPos);
	lua_setglobal(lua, "getPos");

	int error = luaL_dofile(lua, (config::MGE_SCENE_PATH + fileName).c_str());
	if (error) // if non-0, then an error
	{
		// the top of the stack should be the error string
		if (!lua_isstring(lua, lua_gettop(lua)))
			std::cout << "no error" << std::endl;

		// get the top of the stack as the error and pop it off
		std::cout << lua_tostring(lua, lua_gettop(lua)) << std::endl;
		lua_pop(lua, 1);
	}
	else
	{
		// if not an error, then the top of the stack will be the function to call to run the file
		lua_pcall(lua, 0, LUA_MULTRET, 0); // once again, returns non-0 on error, you should probably add a little check
	}
}

void LuaParser::update(float pStep)
{

}
#include "LuaFunctions.h"

#include <iostream>

namespace
{
	void lua_getToStack(luabridge::lua_State* L, const std::string& variableName)
	{
		int level = 0;
		std::string var = "";
		for (int i = 0; i < variableName.size(); i++)
		{
			if (variableName.at(i) == '.')
			{
				if (level == 0)
					lua_getglobal(L, var.c_str());
				else
					lua_getfield(L, -1, var.c_str());

				if (lua_isnil(L, -1))
				{
					std::cout << "Error, can't get " << variableName << std::endl;
					return;
				}
				else
				{
					var = "";
					level++;
				}
			}
			else
			{
				var += variableName.at(i);
			}
		}

		if (level == 0)
			lua_getglobal(L, var.c_str());
		else
			lua_getfield(L, -1, var.c_str());

		if (level == 0)
			return;

		int tableIndex = lua_gettop(L) - level;
		lua_replace(L, tableIndex); //swaps the wanted table to the root one
		lua_settop(L, tableIndex); //pop other tables from the stack
	}
}

bool LuaFunctions::loadScript(luabridge::lua_State* L, const std::string& filename)
{
	if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0))
	{
		std::cout << "Failed to load " << filename << std::endl;
		std::cout << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1); //pop error message from stack
		return false;
	}

	return true;
}

void LuaFunctions::loadGetKeysFunction(luabridge::lua_State* L)
{
	std::string code =
		R"(function getKeys(t)
		s = {}
		for k, v in pairs(t) do
			table.insert(s, k)
			end
		return s
		end)";
	luaL_dostring(L, code.c_str());
}

std::vector<std::string> LuaFunctions::getTableKeys(luabridge::lua_State* L, const std::string& name)
{
	lua_getglobal(L, "getKeys");
	if (lua_isnil(L, -1))
	{
		std::cout << "Get keys function is not loaded. Loading..." << std::endl;
		loadGetKeysFunction(L);
		lua_getglobal(L, "getKeys");
	}

	//table to stack
	lua_getToStack(L, name.c_str());

	// call getKeys function
	lua_pcall(L, 1, 1, 0); // 1 parameter, 1 return

	lua_pushnil(L);

	std::vector<std::string> keys;

	while (lua_next(L, -2))
	{
		if (lua_type(L, -1) == LUA_TSTRING)
			keys.push_back(lua_tostring(L, -1));

		lua_pop(L, 1);
	}

	//remove the s table from the stack
	lua_settop(L, 0);

	return keys;
}
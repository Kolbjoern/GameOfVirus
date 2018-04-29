#pragma once

#include "LuaBridge.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
};

#include <vector>

namespace LuaFunctions 
{
	bool loadScript(luabridge::lua_State* L, const std::string& filename);
	void loadGetKeysFunction(luabridge::lua_State* L);
	std::vector<std::string> getTableKeys(luabridge::lua_State* L, const std::string& name);
}
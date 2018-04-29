#pragma once

#include "LuaBridge.h"

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class Entity;

namespace EntityFunctions
{
	Entity* loadEntity(luabridge::lua_State* L, const std::string& type);
}
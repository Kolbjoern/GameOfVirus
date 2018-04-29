#include "EntityFunctions.h"

#include "../objects/Entity.h"
#include "../utils/LuaFunctions.h"
#include "../components/GraphicsComponent.h"
#include "../components/InputComponent.h"

#include <iostream>

Entity* EntityFunctions::loadEntity(luabridge::lua_State* L, const std::string& type)
{
	using namespace luabridge;
	auto e = new Entity();
	e->setType(type);

	auto v = LuaFunctions::getTableKeys(L, type);
	LuaRef entityTable = getGlobal(L, type.c_str());
	for (auto& componentName : v)
	{
		if (componentName == "GraphicsComponent")
		{
			LuaRef gcTable = entityTable["GraphicsComponent"];
			e->addComponent(
				std::type_index(typeid(GraphicsComponent)),
				new GraphicsComponent(gcTable));
		}
		else if (componentName == "InputComponent")
		{
			LuaRef inputcTable = entityTable["InputComponent"];
			e->addComponent(
				std::type_index(typeid(InputComponent)),
				new InputComponent(inputcTable));
		}
		else
			continue;

		std::cout << "Added " << componentName << " to " << type << std::endl;
	}

	return e;
}
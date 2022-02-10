#include "Effect.hpp"
#include <File/AssetManagerCore.hpp>

Core::uuid Interfaces::Trait<Combat::Effect>::typeId = Core::uuid("ce4cf3dd-435b-41a3-912f-925cfaa8f6b8");

Combat::Element Combat::Effect::getElement()
{
	return Engine::GetModule<Asset::AssetManager>().requestor.requestUniqueInstance<Element>(effectElememtId);
}

Combat::Effect::Effect() : IRequestable()
{
}

Interfaces::TypeInfo Combat::Effect::getTrait() const
{
    return Interfaces::TypeInfo{ Interfaces::Trait<Combat::Effect>::typeId };
}

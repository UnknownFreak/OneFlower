#include "Effect.hpp"
#include <File/Asset/Manager.hpp>

of::common::uuid Interfaces::Trait<Combat::Effect>::typeId = of::common::uuid("ce4cf3dd-435b-41a3-912f-925cfaa8f6b8");

namespace Combat
{

	Element Effect::getElement()
	{
		return Engine::GetModule<File::Asset::Manager>().requestor.requestUniqueInstance<Element>(effectElememtId);
	}

	Effect::Effect() : IRequestable()
	{
	}

	Interfaces::TypeInfo Effect::getTrait() const
	{
		return Interfaces::TypeInfo{ Interfaces::Trait<Effect>::typeId };
	}
};

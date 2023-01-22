#include <combat/effect/Effect.hpp>
#include <file/Handler.hpp>

of::common::uuid of::file::archive::Trait<of::combat::Effect>::typeId = of::common::uuid("ce4cf3dd-435b-41a3-912f-925cfaa8f6b8");

namespace of::combat
{

	Element Effect::getElement()
	{
		return of::engine::GetModule<of::file::Handler>().archive.requestUniqueInstance<Element>(effectElememtId);
	}

	Effect::Effect() : Requestable()
	{
	}

	of::file::archive::TypeInfo Effect::getTrait() const
	{
		return of::file::archive::TypeInfo{ of::file::archive::Trait<Effect>::typeId };
	}
};

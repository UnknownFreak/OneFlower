#include "ModifyObjectActiveState.hpp"

#include <Object/ObjectInstanceHandler.hpp>
#include <File/SaveFile.hpp>

namespace Trigger
{
	void ModifyObjectActiveState::executeInternal()
	{
		if (Engine::GetModule<EngineModule::ObjectInstanceHandler>().exists(gameObjectToModify))
		{
			Engine::GetModule<EngineModule::ObjectInstanceHandler>().getObject(gameObjectToModify)->toggleObjectState(objectState);
		}
		Engine::GetModule<File::SaveFile>().setObjectState(gameObjectToModify, objectState);

	}
	std::unique_ptr<Trigger> ModifyObjectActiveState::clone() const
	{
		return std::make_unique<ModifyObjectActiveState>(*this);
	}
}
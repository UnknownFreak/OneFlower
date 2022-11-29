#include "ObjectStateActivator.hpp"
#include "GameObject.hpp"
#include "ObjectInstanceHandler.hpp"
#include <File/SaveFile.hpp>

Enums::ComponentType Component::IBase<Component::ObjectStateActivator>::typeID = Enums::ComponentType::Activator;
of::common::String Component::IBase<Component::ObjectStateActivator>::componentName = "Activator";

namespace Component
{

	void ObjectStateActivator::toggle()
	{
		auto& saveFile = Engine::GetModule<File::SaveFile>();
		auto& handler = Engine::GetModule<EngineModule::ObjectInstanceHandler>();
		for (auto& [objectId, toggleState] : m_objectsToToggle)
		{
			if (handler.exists(objectId))
			{
				auto object = handler.getObject(objectId);
				if (toggleState == Enums::ObjectState::Toggle)
					object->toggleObjectState();
				else
					object->toggleObjectState(toggleState);
				saveFile.setObjectState(object->id, object->objectState);
			}
		}
	}
	void ObjectStateActivator::onCollision(GameObject*)
	{
	}
	void ObjectStateActivator::Update()
	{
	}
	void ObjectStateActivator::Simulate(const float&)
	{
	}
	void ObjectStateActivator::onDeath()
	{
	}
}
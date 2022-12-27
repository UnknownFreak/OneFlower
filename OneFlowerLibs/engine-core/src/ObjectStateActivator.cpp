#include <object/component/ObjectStateActivator.hpp>

#include <object/GameObject.hpp>
#include <module/ObjectInstanceHandler.hpp>
#include <module/SaveFile.hpp>

of::common::uuid of::object::component::IBase<of::object::component::ObjectStateActivator>::typeID = of::common::uuid("36d49da3-ef84-4856-8a1e-3bfd5fcb1898");
of::common::String of::object::component::IBase<of::object::component::ObjectStateActivator>::componentName = "Activator";

namespace of::object::component
{

	void ObjectStateActivator::onMessage(const of::object::messaging::Message&)
	{
	}

	void ObjectStateActivator::toggle()
	{
		auto& saveFile = of::engine::GetModule<of::module::SaveFile>();
		saveFile;
		auto& handler = of::engine::GetModule<of::module::ObjectInstanceHandler>();
		for (auto& [objectId, toggleState] : m_objectsToToggle)
		{
			if (handler.exists(objectId))
			{
				auto object = handler.getObject(objectId);
				if (toggleState == Enums::ObjectState::Toggle)
					object->toggleObjectState();
				else
					object->toggleObjectState(toggleState);
				// TODO: replace with ObjectStateSaveState
				//saveFile.setObjectState(object->id, object->objectState);
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
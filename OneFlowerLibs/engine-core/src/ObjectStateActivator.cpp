#include <object/component/ObjectStateActivator.hpp>

#include <object/GameObject.hpp>

#include <module/ObjectInstanceHandler.hpp>
#include <module/SaveFile.hpp>

//of::common::uuid of::object::component::IBase<of::object::component::ObjectStateActivator>::typeID = of::common::uuid("36d49da3-ef84-4856-8a1e-3bfd5fcb1898");
//of::common::String of::object::component::IBase<of::object::component::ObjectStateActivator>::componentName = "Activator";

namespace of::object::component
{

	void ObjectStateActivator::onMessage(const of::object::messaging::Message&)
	{
	}

	void ObjectStateActivator::pushObjectSaveState(const of::common::uuid& objectId_, const ObjectState& toggle_)
	{
		objectId_, toggle_;
		auto& saveFile = of::engine::GetModule<of::module::SaveFile>();
		saveFile;
	}

	void ObjectStateActivator::toggle()
	{

		auto& handler = of::engine::GetModule<of::module::ObjectInstanceHandler>();
		for (auto& [objectId, toggleState] : m_objectsToToggle)
		{
			if (handler.exists(objectId))
			{
				auto object = handler.getObject(objectId);
				if (toggleState == ObjectState::Toggle)
					object->toggleObjectState();
				else
					object->toggleObjectState(toggleState);
			}
			else
			{
				if (toggleState != ObjectState::Toggle)
				{
					pushObjectSaveState(objectId, toggleState);
				}
			}
		}
	}
	void ObjectStateActivator::update(const float&)
	{
	}
}
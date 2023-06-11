#include <object/component/ObjectStateActivator.hpp>

#include <object/GameObject.hpp>

#include <module/ObjectInstanceHandler.hpp>
#include <module/SaveFile.hpp>


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
}
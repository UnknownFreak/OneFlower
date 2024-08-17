#include <component/objectStateActivator.hpp>

#include <object/GameObject.hpp>

#include <object/InstanceHandler.hpp>
#include <file/SaveFile.hpp>


namespace of::component
{

	void ObjectStateActivator::onMessage(const of::object::messaging::Message&)
	{
	}

	void ObjectStateActivator::pushObjectSaveState(const of::common::uuid& objectId_, const object::ObjectState& toggle_)
	{
		objectId_, toggle_;
		auto& saveFile = of::engine::GetModule<of::file::SaveFile>();
		saveFile;
	}

	void ObjectStateActivator::toggle()
	{

		auto& handler = of::object::get();
		for (auto& [objectId, toggleState] : m_objectsToToggle)
		{
			if (handler.exists(objectId))
			{
				auto object = handler.getObject(objectId);
				if (toggleState == object::ObjectState::Toggle)
					object->toggleObjectState();
				else
					object->toggleObjectState(toggleState);
			}
			else
			{
				if (toggleState != object::ObjectState::Toggle)
				{
					pushObjectSaveState(objectId, toggleState);
				}
			}
		}
	}
}
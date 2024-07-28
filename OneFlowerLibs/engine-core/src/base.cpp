#include <component/base.hpp>
#include <object/GameObject.hpp>
#include <logger/Logger.hpp>

namespace of::component
{
	namespace
	{
		static size_t instanceCounter = 0;
	};
	
	void Base::attachOn(object::GameObject* attachTo)
	{
		if (attachedOn)
		{
			engine::GetModule<of::logger::Logger>().getLogger("of::component").Debug("Component detached [ComponentType, instanceId]");
			engine::GetModule<of::logger::Logger>().getLogger("of::component").Debug(getTypeName(), ", ", instanceId);
			decouple();
		}
		attachedOn = attachTo;
		if(attachTo->componentMap.find(getType()) == attachTo->componentMap.end())
			// Not UB, all components are allocated with "new" by gameobject...
			// rework and attach the component in the gameobject instead, makes it more clear to what's going on as well.
			// also removes all this "friend shenanigans"
			attachTo->componentMap.insert(std::make_pair(getType(), std::shared_ptr<Base>(this)));
		initialize();
		engine::GetModule<of::logger::Logger>().getLogger("of::component").Debug("Component initialized [ComponentType, instanceId]");
		engine::GetModule<of::logger::Logger>().getLogger("of::component").Debug(getTypeName(), ", ", instanceId);
	}

	void Base::decouple()
	{
		deconstruct();
		attachedOn = nullptr;
	}

	bool Base::post(const of::common::uuid& id, const object::messaging::Topic topic, std::shared_ptr<object::messaging::Body> message) const
	{
		return attachedOn->post(id, topic, message);
	}

	void Base::post(const object::messaging::Topic topic, std::shared_ptr<object::messaging::Body> message) const
	{
		attachedOn->post(topic, message);
	}

	void Base::post(const object::messaging::Message& message) const
	{
		attachedOn->post(message);
	}

	Base::Base() : instanceId(instanceCounter++)
	{
	}
}
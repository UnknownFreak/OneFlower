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
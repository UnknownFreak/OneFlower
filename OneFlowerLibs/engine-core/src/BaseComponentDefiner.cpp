#include <object/component/BaseComponent.hpp>
#include <object/GameObject.hpp>

namespace of::object::component
{
	namespace
	{
		static size_t instanceCounter = 0;
	};
	
	void Base::attachOn(GameObject* attachTo)
	{
		if (attachedOn)
			decouple();
		this->attachedOn = attachTo;
		if(attachTo->componentMap.find(this->getType()) == attachTo->componentMap.end())
			attachTo->componentMap.insert(std::make_pair(this->getType(), std::shared_ptr<Base>(this)));
		initialize();
	}

	void Base::decouple()
	{
		deconstruct();
		attachedOn = nullptr;
	}

	bool Base::post(const of::common::uuid& id, const messaging::Topic topic, std::shared_ptr<messaging::Body> message) const
	{
		return attachedOn->post(id, topic, message);
	}

	void Base::post(const messaging::Topic topic, std::shared_ptr<messaging::Body> message) const
	{
		attachedOn->post(topic, message);
	}

	void Base::post(const messaging::Message& message) const
	{
		attachedOn->post(message);
	}

	Base::Base() : instanceId(instanceCounter++)
	{
	}
}
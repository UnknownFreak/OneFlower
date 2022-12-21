#include <object/component/BaseComponent.hpp>
#include <object/GameObject.hpp>

namespace of::object::component
{
	void Base::attachOn(GameObject* attachTo)
	{
		if (attachedOn)
			detach();
		this->attachedOn = attachTo;
		if(attachTo->componentMap.find(this->getType()) == attachTo->componentMap.end())
			attachTo->componentMap.insert(std::make_pair(this->getType(), std::shared_ptr<Base>(this)));
	}

	void component::Base::post(const messaging::Topic topic, std::shared_ptr<messaging::Body> message) const
	{
		attachedOn->post(topic, message);
	}

	void component::Base::post(const messaging::Message& message) const
	{
		attachedOn->post(message);
	}
}
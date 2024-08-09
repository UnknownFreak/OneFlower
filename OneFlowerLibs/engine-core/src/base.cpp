#include <component/base.hpp>
#include <object/GameObject.hpp>
#include <logger/Logger.hpp>

namespace of::component
{
	void Base::attach()
	{
		attached();
		of::logger::get().getLogger("of::component").Debug("Component attached [ComponentType]");
		of::logger::get().getLogger("of::component").Debug(getTypeName());
	}

	void Base::decouple()
	{
		of::logger::get().getLogger("of::component").Debug("Component decoupled [ComponentType]");
		of::logger::get().getLogger("of::component").Debug(getTypeName());
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

	Base::Base() : subscriberId(0)
	{
	}

	Base::Base(const Base& ) : Base()
	{
	}
}
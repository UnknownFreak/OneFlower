#include <messaging/courier.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::messaging::Courier>::type = of::module::EngineResourceType::Courier;

namespace of::messaging
{


	void of::messaging::Courier::post(const Topic& topic, std::shared_ptr<Message> message)
	{
		channels[topic]->sendMessage(message);
	}
}

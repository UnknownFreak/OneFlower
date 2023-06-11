#pragma once

#include <utils/common/uuid.hpp>
#include <utils/lifetime/warranty.hpp>

#include <module/logger/OneLogger.hpp>

#include <functional>


namespace of::messaging
{
	class Subscriber
	{
	public:

		Subscriber() : m_ptr(), warranty(of::utils::lifetime::Warranty::makeInvalid())
		{
		}

		Subscriber(const of::utils::lifetime::Warranty& warranty, const std::function<void(const Message&)>& function) : m_ptr(function), warranty(warranty)
		{
		}

		void sendMessage(const Message& message)
		{
			if (warranty)
			{
				m_ptr(message);
			}
			else
			{
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::Subscriber").Warning("Trying to send a message to an object that is no longer guaranteed by warranty.");
			}
		}

	private:

		std::function<void(const Message&)> m_ptr;
		of::utils::lifetime::Warranty warranty;
	};

	template<class T>
	class BasicMessageSubscriber : public Subscriber
	{
	public:
		BasicMessageSubscriber(const of::utils::lifetime::Warranty& warranty, const std::function<void(const T&)>& function) :
			Subscriber(warranty, [function](const Message& msg) {function(msg.as<BasicMessage<T>>().value); })
		{
		}
	};
}

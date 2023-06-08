#pragma once

#include <utils/common/uuid.hpp>

#include <messaging/lifetime/warranty.hpp>
#include <module/logger/OneLogger.hpp>

#include <functional>


namespace of::messaging
{
	class Subscriber
	{
		of::common::uuid m_id;

	public:

		Subscriber(lifetime::Warranty& warranty, std::function<void(const Message&)>function) : m_id(), m_ptr(function), warranty(warranty)
		{
		}

		of::common::uuid& getId()
		{
			return m_id;
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
		lifetime::Warranty warranty;
	};
}

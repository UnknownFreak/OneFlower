#pragma once

#include <utils/common/uuid.hpp>
#include <functional>

namespace of::messaging
{
	class Subscriber
	{
		of::common::uuid m_id;

	public:

		Subscriber(std::function<void(std::shared_ptr<Message>)>function) : m_id(), m_ptr(function)
		{
		}

		of::common::uuid& getId()
		{
			return m_id;
		}

		void sendMessage(std::shared_ptr<Message>message)
		{
			m_ptr(message);
		}

	private:

		std::function<void(std::shared_ptr<Message>)> m_ptr;

	};
}

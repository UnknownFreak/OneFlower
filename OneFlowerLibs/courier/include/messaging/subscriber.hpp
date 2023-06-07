#pragma once

#include <utils/common/uuid.hpp>
#include <functional>

namespace of::messaging
{
	class Subscriber
	{
		of::common::uuid m_id;

	public:

		Subscriber(std::function<void(const Message&)>function) : m_id(), m_ptr(function)
		{
		}

		of::common::uuid& getId()
		{
			return m_id;
		}

		void sendMessage(const Message& message)
		{
			m_ptr(message);
		}

	private:

		std::function<void(const Message&)> m_ptr;

	};
}

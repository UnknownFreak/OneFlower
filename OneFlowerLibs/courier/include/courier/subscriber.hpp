#pragma once

#include <courier/message.hpp>

#include <utils/common/uuid.hpp>

#include <functional>

namespace of::courier
{
	class Subscriber
	{
	public:

		Subscriber(const size_t id = 0);

		Subscriber(const size_t id, const std::weak_ptr<bool>& isAlive, const std::function<void(const courier::Message&)>& function);

		Subscriber(const Subscriber& sub);

		void sendMessage(const courier::Message& message);

		Subscriber& operator=(const Subscriber& other);

		bool operator < (const Subscriber& other) const;
		bool operator ==(const Subscriber& other) const;

	private:

		std::function<void(const courier::Message&)> m_ptr;
		std::weak_ptr<bool> m_isAlive;
		size_t id;
	};
}

#pragma once

#include <courier/message.hpp>

#include <utils/common/uuid.hpp>

#include <functional>

namespace of::courier
{
	class Subscriber
	{
	public:

		Subscriber();

		Subscriber(const std::weak_ptr<bool>& isAlive, const std::function<void(const courier::Message&)>& function);

		Subscriber(const Subscriber& sub);

		void sendMessage(const courier::Message& message);

		Subscriber(Subscriber&& other) noexcept
			: id(std::move(other.id))
			, m_ptr(std::move(other.m_ptr))
			, m_isAlive(std::move(other.m_isAlive))
		{
		}

		Subscriber& operator=(const Subscriber& other);
		Subscriber& operator=(Subscriber&& other)
		{
			id = std::move(other.id);
			m_ptr = std::move(other.m_ptr);
			m_isAlive = std::move(other.m_isAlive);
			return *this;
		}


		bool operator < (const Subscriber& other) const;
		bool operator ==(const Subscriber& other) const;

		size_t id;
	private:

		std::function<void(const courier::Message&)> m_ptr;
		std::weak_ptr<bool> m_isAlive;
	};
}

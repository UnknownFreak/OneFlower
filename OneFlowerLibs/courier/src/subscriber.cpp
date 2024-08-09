#include <courier/subscriber.hpp>

#include <logger/Logger.hpp>

// reserve zero for un-initialized
size_t g_subscriberId = 1;

namespace of::courier
{

	Subscriber::Subscriber() : m_ptr(), m_isAlive(), id(0)
	{
	}

	Subscriber::Subscriber(const std::weak_ptr<bool>& isAlive, const std::function<void(const Message&)>& function) : m_ptr(function), m_isAlive(isAlive), id(g_subscriberId++)
	{
	}

	Subscriber::Subscriber(const Subscriber& sub) : m_ptr(sub.m_ptr), m_isAlive(sub.m_isAlive), id(sub.id)
	{
	}

	void Subscriber::sendMessage(const Message& message)
	{
		if (m_isAlive.expired() == false)
		{
			m_ptr(message);
		}
		else
		{
			of::logger::get().getLogger("of::messaging::Subscriber").Warning("Trying to send a message to an object that is no longer guaranteed by warranty.");
		}
	}

	Subscriber& Subscriber::operator=(const Subscriber& other)
	{
		if (this == &other)
		{
			return *this;
		}

		m_ptr = other.m_ptr;
		m_isAlive = other.m_isAlive;
		id = other.id;
		return *this;
	}

	bool Subscriber::operator < (const Subscriber& other) const
	{
		return id < other.id;
	}

	bool Subscriber::operator ==(const Subscriber& other) const
	{
		return id == other.id;
	}
}

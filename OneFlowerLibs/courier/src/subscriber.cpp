#include <courier/subscriber.hpp>

#include <logger/OneLogger.hpp>


namespace of::courier
{

	Subscriber::Subscriber(const size_t id) : m_ptr(), m_isAlive(), id(id)
	{
	}

	Subscriber::Subscriber(const size_t id, const std::weak_ptr<bool>& isAlive, const std::function<void(const Message&)>& function) : m_ptr(function), m_isAlive(isAlive), id(id)
	{
	}

	Subscriber::Subscriber(const Subscriber& sub) : Subscriber(sub.id, sub.m_isAlive, sub.m_ptr)
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
			of::engine::GetModule<of::logger::OneLogger>().getLogger("of::messaging::Subscriber").Warning("Trying to send a message to an object that is no longer guaranteed by warranty.");
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

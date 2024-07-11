#include <courier/subscriber.hpp>

#include <module/logger/OneLogger.hpp>


namespace of::courier
{

	Subscriber::Subscriber(const size_t id) : m_ptr(), warranty(of::utils::lifetime::Warranty::makeInvalid()), id(id)
	{
	}

	Subscriber::Subscriber(const size_t id, const of::utils::lifetime::Warranty& warranty, const std::function<void(const Message&)>& function) : m_ptr(function), warranty(warranty), id(id)
	{
	}

	Subscriber::Subscriber(const Subscriber& sub) : Subscriber(sub.id, sub.warranty, sub.m_ptr)
	{
	}

	void Subscriber::sendMessage(const Message& message)
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

	Subscriber& Subscriber::operator=(const Subscriber& other)
	{
		if (this == &other)
		{
			return *this;
		}

		m_ptr = other.m_ptr;
		warranty = other.warranty;
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

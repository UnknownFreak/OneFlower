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

		Subscriber(const size_t id =0) : m_ptr(), warranty(of::utils::lifetime::Warranty::makeInvalid()), id(id)
		{
		}

		Subscriber(const size_t& id, const of::utils::lifetime::Warranty& warranty, const std::function<void(const Message&)>& function) : m_ptr(function), warranty(warranty), id(id)
		{
		}

		Subscriber(const Subscriber& sub) : Subscriber(sub.id, sub.warranty, sub.m_ptr)
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

		Subscriber& operator=(const Subscriber& other)
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

		bool operator < (const Subscriber& other) const
		{
			return id < other.id;
		}

		bool operator ==(const Subscriber& other) const
		{
			return id == other.id;
		}

	private:

		std::function<void(const Message&)> m_ptr;
		of::utils::lifetime::Warranty warranty;
		size_t id;
	};
}

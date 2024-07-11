#pragma once

#include <courier/message.hpp>

#include <utils/common/uuid.hpp>
#include <utils/lifetime/warranty.hpp>

#include <functional>

namespace of::courier
{
	class Subscriber
	{
	public:

		Subscriber(const size_t id = 0);

		Subscriber(const size_t id, const of::utils::lifetime::Warranty& warranty, const std::function<void(const courier::Message&)>& function);

		Subscriber(const Subscriber& sub);

		void sendMessage(const courier::Message& message);

		Subscriber& operator=(const Subscriber& other);

		bool operator < (const Subscriber& other) const;
		bool operator ==(const Subscriber& other) const;

	private:

		std::function<void(const courier::Message&)> m_ptr;
		of::utils::lifetime::Warranty warranty;
		size_t id;
	};
}

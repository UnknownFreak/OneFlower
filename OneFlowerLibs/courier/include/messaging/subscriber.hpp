#pragma once

#include <utils/common/uuid.hpp>

namespace of::messaging
{
	class Subscriber
	{
		of::common::uuid m_id;

	public:

		Subscriber() : m_id()
		{

		}

		of::common::uuid& getId()
		{
			return m_id;
		}

	private:

	};
}

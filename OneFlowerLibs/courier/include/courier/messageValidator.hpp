#pragma once

#include <courier/message.hpp>

namespace of::courier
{
	class MessageValidator
	{
	public:

		inline virtual bool validate(const Message& message) = 0;
	};

}
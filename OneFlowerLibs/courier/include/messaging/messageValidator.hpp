#pragma once

#include <messaging/message.hpp>
#include <module/logger/OneLogger.hpp>

namespace of::messaging
{
	class MessageValidator
	{
	public:

		inline virtual bool validate(const of::messaging::Message& message) = 0;
	};


	template<std::derived_from<Message> T>
	class IsMessageTypeValidator : public MessageValidator
	{
		virtual inline bool validate(const of::messaging::Message& message) override
		{
			if (message.is<T>() == false)
			{
				auto& logger = of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::messaging::IsMessageTypeValidator");
				logger.Info("Message validator failed to validate message [checked, requiredType]", message.toString(), ", ", T().toString());
				return false;
			}
			return true;
		}
	};
}
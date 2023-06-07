#pragma once
#include <messaging/message.hpp>

namespace of::messaging
{

	template<class T>
	class BasicMessage : public Message
	{
	public:

		constexpr BasicMessage() : BasicMessage(T())
		{
		}

		constexpr BasicMessage(const T& t) : Message(MessageTypeHelper::GetBasicType<T>(), MessageTypeHelper::GetBasicTypeId<T>()), value(t)
		{
		}
		const T value;

	protected:

		constexpr BasicMessage(const T& t, const unsigned int& customId) : Message(MessageType::CUSTOM, customId), value(t)
		{
		}
	};
}

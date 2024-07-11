#include <courier/message.hpp>

namespace of::courier
{
	Message::Message() : msgType{}, m_arg()
	{
	}

	Message::Message(const MessageType type) : msgType(type), m_arg()
	{
	}

	Message::Message(const Message& other) : msgType(other.msgType), m_arg(other.m_arg)
	{
	}

	Message& Message::operator=(const Message& other)
	{
		msgType = other.msgType;
		m_arg = other.m_arg;
		return *this;
	}
}

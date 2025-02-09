#include <input/windowChannel.hpp>

#include <input/inputEvents.hpp>

#include <engine/courier/messageType.hpp>

#include <logger/Logger.hpp>

namespace of::input
{

	WindowChannel::WindowChannel(const of::common::String& windowName) : Channel(0)
	{
		setChannelName(windowName);
	}

	size_t WindowChannel::sendMessage(const courier::Message& message)
	{
		auto msgType = message.as<courier::MessageType>();
		switch (msgType)
		{
		case courier::MessageType::InputAxisEvent:
			return gamePadChannel.sendAxisMessage(message);
		case courier::MessageType::InputHoldEvent:
		case courier::MessageType::InputPressEvent:
		case courier::MessageType::InputReleaseEvent:
			return sentToCorrectChannel(message);
		default:
			logger::get().getLogger("of::input::WindowChannel").Error("invalid message type, [", (size_t)msgType, "]");
			break;
		}
		return 0u;
	}

	size_t WindowChannel::sendMessage(const courier::SubscriberId, const courier::Message&)
	{
		logger::get().getLogger("of::input::WindowChannel").Error("Cannot send message to a specific subscriber");
		return 0u;
	}

	size_t WindowChannel::sendMessage(const courier::ChannelId, const courier::Message&)
	{
		logger::get().getLogger("of::input::WindowChannel").Error("Cannot send message to a specific channel");
		return 0u;
	}

	size_t WindowChannel::sendMessage(const courier::ChannelId, const courier::SubscriberId, const courier::Message&)
	{
		logger::get().getLogger("of::input::WindowChannel").Error("Cannot send message to a specific subscriber on a specific channel");
		return 0u;
	}

	size_t WindowChannel::sentToCorrectChannel(const courier::Message& msg)
	{
		const auto val = msg.get<input::InputEvent>();
		switch (val.inputType)
		{
		case of::input::InputType::GamePadButton:
			return gamePadChannel.handleInputMessage(msg);
		case of::input::InputType::Keyboard:
			return keyboardChannel.handleInputMessage(msg);
		case of::input::InputType::Mouse:
			return mouseChannel.handleInputMessage(msg);
		default:
			logger::get().getLogger("of::input::WindowChannel").Error("invalid input type, [", (size_t)val.inputType, "]");
			break;
		}
		return 0u;
	}

}
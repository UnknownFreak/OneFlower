#include <input/keyboardChannel.hpp>

#include <engine/courier/messageType.hpp>

#include <courier/util.hpp>

namespace of::input
{
	KeyboardChannel::KeyboardChannel()
	{
	}

	size_t KeyboardChannel::handleInputMessage(const courier::Message& message)
	{
		switch (message.as<courier::MessageType>())
		{
		case courier::MessageType::InputPressEvent:
			return sendPressMessage(message);
		case courier::MessageType::InputHoldEvent:
			return sendHoldMessage(message);
		case courier::MessageType::InputReleaseEvent:
			return sendReleaseMessage(message);
		default: return 0;
		}
	}

	of::common::uuid KeyboardChannel::on(const InputStateType type, const of::input::Keys button, const RegularInputBind& bind)
	{
		switch (type)
		{
		case InputStateType::Press:
			keyboardButton_Press[button].push_back(bind);
			return bind.id;
		case InputStateType::Hold:
			keyboardButton_Hold[button].push_back(bind);
			return bind.id;
		case InputStateType::Release:
			keyboardButton_Release[button].push_back(bind);
			return bind.id;
		}
		return of::common::uuid::nil();
	}

	void KeyboardChannel::removeBind(const of::input::Keys button, const of::common::uuid& bindId)
	{
		std::vector<of::common::uuid> b{ bindId };
		courier::util::vectorFastRemove(keyboardButton_Press[button], b);
		b.push_back(bindId);
		courier::util::vectorFastRemove(keyboardButton_Hold[button], b);
		b.push_back(bindId);
		courier::util::vectorFastRemove(keyboardButton_Release[button], b);
	}

	void KeyboardChannel::moveBind(const of::input::Keys oldButton, const of::input::Keys newButton)
	{
		std::swap(keyboardButton_Press[oldButton], keyboardButton_Press[newButton]);
		std::swap(keyboardButton_Hold[oldButton], keyboardButton_Hold[newButton]);
		std::swap(keyboardButton_Release[oldButton], keyboardButton_Release[newButton]);
	}

	size_t KeyboardChannel::sendPressMessage(const courier::Message& message)
	{
		auto& cont = keyboardButton_Press[message.get<InputEvent>().getKeyboardKey()];
		for (auto& it : cont)
		{
			it.m_func();
		}
		return cont.size();

	}

	size_t KeyboardChannel::sendHoldMessage(const courier::Message& message)
	{
		auto& cont = keyboardButton_Hold[message.get<InputEvent>().getKeyboardKey()];
		for (auto& it : cont)
		{
			it.m_func();
		}
		return cont.size();
	}

	size_t KeyboardChannel::sendReleaseMessage(const courier::Message& message)
	{
		auto& cont = keyboardButton_Release[message.get<InputEvent>().getKeyboardKey()];
		for (auto& it : cont)
		{
			it.m_func();
		}
		return cont.size();
	}
}
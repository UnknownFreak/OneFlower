#include <input/mouseChannel.hpp>

#include <engine/courier/messageType.hpp>

#include <courier/util.hpp>

namespace of::input
{
	MouseChannel::MouseChannel()
	{

	}

	size_t MouseChannel::handleInputMessage(const courier::Message& message)
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

	of::common::uuid MouseChannel::on(const InputStateType type, const of::input::Mouse button, const RegularInputBind& bind)
	{
		switch (type)
		{
		case InputStateType::Press:
			mouseButton_Press[button].push_back(bind);
			return bind.id;
		case InputStateType::Hold:
			mouseButton_Hold[button].push_back(bind);
			return bind.id;
		case InputStateType::Release:
			mouseButton_Release[button].push_back(bind);
			return bind.id;
		}
		return of::common::uuid::nil();
	}

	void MouseChannel::removeBind(const of::common::uuid& bindId)
	{
		std::vector<of::common::uuid> b{ bindId };
		for (auto& v : mouseButton_Hold)
		{
			courier::util::vectorFastRemove(v.second, b, true);
		}
		for (auto& v : mouseButton_Press)
		{
			courier::util::vectorFastRemove(v.second, b, true);
		}
		for (auto& v : mouseButton_Release)
		{
			courier::util::vectorFastRemove(v.second, b, true);
		}
	}

	void MouseChannel::removeBind(const of::input::Mouse button, const of::common::uuid& bindId)
	{
		std::vector<of::common::uuid> b{ bindId };
		courier::util::vectorFastRemove(mouseButton_Press[button], b);
		b.push_back(bindId);
		courier::util::vectorFastRemove(mouseButton_Hold[button], b);
		b.push_back(bindId);
		courier::util::vectorFastRemove(mouseButton_Release[button], b);
	}

	void MouseChannel::moveBind(const of::input::Mouse oldButton, const of::input::Mouse newButton)
	{
		std::swap(mouseButton_Press[oldButton], mouseButton_Press[newButton]);
		std::swap(mouseButton_Hold[oldButton], mouseButton_Hold[newButton]);
		std::swap(mouseButton_Release[oldButton], mouseButton_Release[newButton]);
	}

	size_t MouseChannel::sendPressMessage(const courier::Message& message)
	{
		auto& cont = mouseButton_Press[message.get<InputEvent>().getMouseButton()];
		for (auto& it : cont)
		{
			it.m_func();
		}
		return cont.size();

	}

	size_t MouseChannel::sendHoldMessage(const courier::Message& message)
	{
		auto& cont = mouseButton_Hold[message.get<InputEvent>().getMouseButton()];
		for (auto& it : cont) 
		{
			it.m_func();
		}
		return cont.size();
	}

	size_t MouseChannel::sendReleaseMessage(const courier::Message & message)
	{
		auto& cont = mouseButton_Release[message.get<InputEvent>().getMouseButton()];
		for (auto& it : cont) 
		{
			it.m_func();
		}
		return cont.size();
	}
}
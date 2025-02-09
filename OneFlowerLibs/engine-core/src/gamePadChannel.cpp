#include <input/gamePadChannel.hpp>

#include <engine/courier/messageType.hpp>

#include <courier/util.hpp>

namespace of::input
{
	GamePadChannel::GamePadChannel()
	{
	}

	size_t GamePadChannel::sendAxisMessage(const courier::Message& axisMessage)
	{
		auto axisEvent = axisMessage.get<AxisEvent>();
		auto& cont = axisKeybinds[axisEvent.axis];
		for (auto& it : cont)
		{
			it.m_func(axisEvent.valueType);
		}
		return cont.size();
	}

	size_t GamePadChannel::handleInputMessage(const courier::Message& message)
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

	of::common::uuid GamePadChannel::on(const of::input::GamePadAxis button, const AxisInputBind& bind)
	{
		axisKeybinds[button].push_back(bind);
		return bind.id;
	}

	of::common::uuid GamePadChannel::on(const InputStateType type, const of::input::GamePadButton button, const RegularInputBind& bind)
	{
		switch (type)
		{
		case InputStateType::Press:
			gamePadButton_Press[button].push_back(bind);
			return bind.id;
		case InputStateType::Hold:
			gamePadButton_Hold[button].push_back(bind);
			return bind.id;
		case InputStateType::Release:
			gamePadButton_Release[button].push_back(bind);
			return bind.id;
		}
		return of::common::uuid::nil();
	}

	void GamePadChannel::removeBind(const of::common::uuid& bind)
	{
		std::vector<of::common::uuid> b{ bind };
		for (auto& v : axisKeybinds)
		{
			courier::util::vectorFastRemove(v.second, b, true);
		}

		for (auto& v : gamePadButton_Press)
		{
			courier::util::vectorFastRemove(v.second, b, true);
		}

		for (auto& v : gamePadButton_Hold)
		{
			courier::util::vectorFastRemove(v.second, b, true);
		}

		for (auto& v : gamePadButton_Release)
		{
			courier::util::vectorFastRemove(v.second, b, true);
		}
	}

	void GamePadChannel::removeBind(const of::input::GamePadAxis button, const of::common::uuid& bindId)
	{
		std::vector<of::common::uuid> b{ bindId };
		courier::util::vectorFastRemove(axisKeybinds[button], b);
	}

	void GamePadChannel::removeBind(const of::input::GamePadButton button, const of::common::uuid& bindId)
	{
		std::vector<of::common::uuid> b{ bindId };
		courier::util::vectorFastRemove(gamePadButton_Press[button], b, true);
		courier::util::vectorFastRemove(gamePadButton_Hold[button], b, true);
		courier::util::vectorFastRemove(gamePadButton_Release[button], b, true);
	}

	void GamePadChannel::moveBind(const of::input::GamePadAxis oldButton, const of::input::GamePadAxis newButton)
	{
		std::swap(axisKeybinds[oldButton], axisKeybinds[newButton]);
	}

	void GamePadChannel::moveBind(const of::input::GamePadButton oldButton, const of::input::GamePadButton newButton)
	{
		std::swap(gamePadButton_Press[oldButton], gamePadButton_Press[newButton]);
		std::swap(gamePadButton_Hold[oldButton], gamePadButton_Hold[newButton]);
		std::swap(gamePadButton_Release[oldButton], gamePadButton_Release[newButton]);
	}

	size_t GamePadChannel::sendPressMessage(const courier::Message& message)
	{
		auto& cont = gamePadButton_Press[message.get<InputEvent>().getControllerButton()];
		for (auto& it : cont)
		{
			it.m_func();
		}
		return cont.size();

	}

	size_t GamePadChannel::sendHoldMessage(const courier::Message& message)
	{
		auto& cont = gamePadButton_Hold[message.get<InputEvent>().getControllerButton()];
		for (auto& it : cont)
		{
			it.m_func();
		}
		return cont.size();
	}

	size_t GamePadChannel::sendReleaseMessage(const courier::Message& message)
	{
		auto& cont = gamePadButton_Release[message.get<InputEvent>().getControllerButton()];
		for (auto& it : cont)
		{
			it.m_func();
		}
		return cont.size();
	}
}
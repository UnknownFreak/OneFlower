#include <input/inputSource.hpp>

#include <courier/courier.hpp>
#include <engine/courier/topic.hpp>
#include <engine/courier/messageType.hpp>

namespace of::input
{

	InputSource::InputSource(const of::common::String& windowName) : m_channel(std::make_shared<WindowChannel>(windowName))
	{
		using Topic = of::engine::courier::Topic;
		constexpr auto from = of::Topic::convert;
		courier::get().getChannel(from(Topic::Input))->addChannel(m_channel);
		m_id = m_channel->getId();
	}

	of::common::uuid InputSource::on(GamePadAxis axis, std::function<void(const float)>& func)
	{
		return m_channel->on(axis, func);
	}

	of::common::uuid InputSource::on(const InputStateType messageType, const Mouse button, std::function<void(void)>& func)
	{
		return m_channel->on(messageType, button, func);
	}

	of::common::uuid InputSource::on(const InputStateType messageType, const Keys button, std::function<void(void)>& func)
	{
		return m_channel->on(messageType, button, func);
	}

	of::common::uuid InputSource::on(const InputStateType messageType, const GamePadButton button, std::function<void(void)>& func)
	{
		return m_channel->on(messageType, button, func);
	}

	InputSource::~InputSource()
	{
		using Topic = of::engine::courier::Topic;
		constexpr auto from = of::Topic::convert;
		courier::get().getChannel(from(Topic::Input))->removeChannel(getId());
	}

	void InputSource::dispatchEvents()
	{
		using Topic = of::engine::courier::Topic;
		constexpr auto from = of::Topic::convert;
		constexpr auto to = of::Topic::convert;
		if (courier::get().getScheduledMessageCount(from(Topic::Input)) == 0)
		{
			auto& courier = courier::get();
			for (auto& button : m_eventDispatcher.mMouseButtonValues)
			{
				if (button.second.press)
				{
					courier.schedule(to(Topic::Input), courier::Message(courier::MessageType::InputPressEvent,
						InputEvent{ InputType::Mouse, (U32)button.first }));
					button.second.press = false;
				}
				if (button.second.hold)
				{
					courier.schedule(to(Topic::Input), courier::Message(courier::MessageType::InputHoldEvent,
						InputEvent{ InputType::Mouse, (U32)button.first }));
				}
				if (button.second.release)
				{
					courier.schedule(to(Topic::Input), courier::Message(courier::MessageType::InputReleaseEvent,
						InputEvent{ InputType::Mouse, (U32)button.first }));
					button.second.release = false;
				}
			}
			for (auto& key : m_eventDispatcher.mKeysValues)
			{
				if (key.second.press)
				{
					courier.schedule(to(Topic::Input), courier::Message(courier::MessageType::InputPressEvent,
						InputEvent{ InputType::Keyboard, (U32)key.first }));
					key.second.press = false;
				}
				if (key.second.hold)
				{
					courier.schedule(to(Topic::Input), courier::Message(courier::MessageType::InputHoldEvent,
						InputEvent{ InputType::Keyboard, (U32)key.first }));
				}
				if (key.second.release)
				{
					courier.schedule(to(Topic::Input), courier::Message(courier::MessageType::InputReleaseEvent,
						InputEvent{ InputType::Keyboard, (U32)key.first }));
					key.second.release = false;
				}
			}
			for (auto& padButton : m_eventDispatcher.mGamePadButtonValues)
			{
				if (padButton.second.press)
				{
					courier.schedule(to(Topic::Input), courier::Message(courier::MessageType::InputPressEvent,
						InputEvent{ InputType::GamePadButton, (U32)padButton.first }));
					padButton.second.press = false;
				}
				if (padButton.second.hold)
				{
					courier.schedule(to(Topic::Input), courier::Message(courier::MessageType::InputHoldEvent,
						InputEvent{ InputType::GamePadButton, (U32)padButton.first }));
				}
				if (padButton.second.release)
				{
					courier.schedule(to(Topic::Input), courier::Message(courier::MessageType::InputReleaseEvent,
						InputEvent{ InputType::GamePadButton, (U32)padButton.first }));
					padButton.second.release = false;
				}
			}
			for (auto& padAxis : m_eventDispatcher.mGamePadAxisValues)
			{
				if (std::fabs(padAxis.second.current - padAxis.second.previous) > 0.001f)
				{
					courier.schedule(to(Topic::Input), getId(), courier::Message(courier::MessageType::InputAxisEvent,
						AxisEvent{ padAxis.first, padAxis.second.current }));
				}
			}
		}
	}

	void InputSource::publishEvent(const swizzle::core::WindowEvent& event)
	{
		switch (event.getEventType())
		{
		case swizzle::core::WindowEventType::GamepadAxisEvent:
		{
			handleGamePadAxisEvent((swizzle::core::GamepadAxisEvent&)event);
			break;
		}
		case swizzle::core::WindowEventType::GamepadButtonEvent:
		{
			handleGamePadButtonEvent((swizzle::core::GamepadButtonEvent&)event);
			break;
		}
		case swizzle::core::WindowEventType::KeyboardInputEvent:
		{
			handleKeyboardInputEvent((swizzle::core::InputEvent&)event);
			break;
		}
		case swizzle::core::WindowEventType::FocusEvent:
		{
			handleWindowFocusEvent((swizzle::core::WindowFocusEvent&)event);
			break;
		}
		default:
			break;
		}
	}

	void InputSource::handleGamePadAxisEvent(const swizzle::core::GamepadAxisEvent& event)
	{
		m_eventDispatcher.mGamePadAxisValues[event.mAxis].current = event.mAxisValue;
	}

	void InputSource::handleGamePadButtonEvent(const swizzle::core::GamepadButtonEvent& event)
	{
		m_eventDispatcher.mGamePadButtonValues[event.mButton].press = event.mButtonPressed;
		if (event.mButtonPressed)
		{
			m_eventDispatcher.mGamePadButtonValues[event.mButton].press = event.mButtonPressed;
			m_eventDispatcher.mGamePadButtonValues[event.mButton].hold = event.mButtonPressed;
		}
		else
		{
			m_eventDispatcher.mGamePadButtonValues[event.mButton].hold = false;
			m_eventDispatcher.mGamePadButtonValues[event.mButton].release = true;
		}
	}

	void InputSource::handleKeyboardInputEvent(const swizzle::core::InputEvent& event)
	{
		if (event.mFromKeyboard)
		{
			if (event.mPressed)
			{
				if (m_eventDispatcher.mKeysValues[(Keys)event.mKey].hold == false)
				{
					m_eventDispatcher.mKeysValues[(Keys)event.mKey].press = event.mPressed;
					m_eventDispatcher.mKeysValues[(Keys)event.mKey].hold = event.mPressed;
				}
			}
			else
			{
				m_eventDispatcher.mKeysValues[(Keys)event.mKey].hold = false;
				m_eventDispatcher.mKeysValues[(Keys)event.mKey].release = true;
			}
		}
		else
		{
			if (event.mPressed)
			{
				m_eventDispatcher.mMouseButtonValues[(Mouse)event.mKey].press = event.mPressed;
				m_eventDispatcher.mMouseButtonValues[(Mouse)event.mKey].hold = event.mPressed;
			}
			else
			{
				m_eventDispatcher.mMouseButtonValues[(Mouse)event.mKey].hold = false;
				m_eventDispatcher.mMouseButtonValues[(Mouse)event.mKey].release = true;
			}
		}
	}

	void InputSource::handleWindowFocusEvent(const swizzle::core::WindowFocusEvent& event)
	{
		if (event.mFocused == false)
		{
			for (auto& state : m_eventDispatcher.mMouseButtonValues)
			{
				resetState(state.second);
			}
			for (auto& state : m_eventDispatcher.mGamePadButtonValues)
			{
				resetState(state.second);
			}
			for (auto& state : m_eventDispatcher.mKeysValues)
			{
				resetState(state.second);
			}
			for (auto& state : m_eventDispatcher.mGamePadAxisValues)
			{
				state.second.previous = state.second.current;
			}
		}
	}

	void InputSource::resetState(ButtonState& state)
	{
		if (state.hold)
		{
			state.press = false;
			state.hold = false;
			state.release = true;
		}
	}

}
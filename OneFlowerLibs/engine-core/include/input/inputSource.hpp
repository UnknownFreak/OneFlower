#pragma once

#include <utils/common/uuid.hpp>

#include <swizzle/core/Input.hpp>
#include <input/inputEvents.hpp>
#include <input/inputEventDispatcher.hpp>
#include <input/inputFunctionBind.hpp>
#include <input/windowChannel.hpp>

#include <engine/courier/messageType.hpp>

namespace of::input
{

	class InputSource : public swizzle::EventHandler<swizzle::core::WindowEvent>
	{

	public:

		InputSource(const of::common::String& windowName);
		~InputSource();

		of::common::uuid on(const GamePadAxis axis, const std::function<void(const float)>& func);
		of::common::uuid on(const InputStateType messageType, const Mouse button, const std::function<void(void)>& func);
		of::common::uuid on(const InputStateType messageType, const Keys button, const std::function<void(void)>& func);
		of::common::uuid on(const InputStateType messageType, const GamePadButton button, const std::function<void(void)>& func);

		void removeBind(const of::common::uuid& id);

		void dispatchEvents();

		inline const courier::ChannelId getId() const { return m_id; };

		bool wasKeybindPressed(const Keys button);

	private:

		void publishEvent(const swizzle::core::WindowEvent& event) override;

		void handleGamePadAxisEvent(const swizzle::core::GamepadAxisEvent& event);
		void handleGamePadButtonEvent(const swizzle::core::GamepadButtonEvent& event);
		void handleKeyboardInputEvent(const swizzle::core::InputEvent& event);
		void handleWindowFocusEvent(const swizzle::core::WindowFocusEvent& event);

		void resetState(ButtonState& state);

		std::shared_ptr<WindowChannel> m_channel;
		InputEventDispatcher m_eventDispatcher;
		courier::ChannelId m_id;

	};

}
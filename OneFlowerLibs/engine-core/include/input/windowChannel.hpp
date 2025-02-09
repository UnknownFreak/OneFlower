#pragma once

#include <courier/channel.hpp>

#include <input/gamePadChannel.hpp>
#include <input/mouseChannel.hpp>
#include <input/keyboardChannel.hpp>

#include <utils/common/string.hpp>

namespace of::input
{

	class WindowChannel : public courier::Channel
	{

	public:
		WindowChannel(const of::common::String& windowName);

		size_t sendMessage(const courier::Message& message) override;
		size_t sendMessage(const courier::SubscriberId subscriberId, const courier::Message& message) override;
		size_t sendMessage(const courier::ChannelId channelId, const courier::Message& message);
		size_t sendMessage(const courier::ChannelId channelId, const courier::SubscriberId subscriberId, const courier::Message& message);

		of::common::uuid on(const GamePadAxis axis, const std::function<void(const float)>& func);
		of::common::uuid on(const InputStateType messageType, const Mouse button, const std::function<void(void)>& func);
		of::common::uuid on(const InputStateType messageType, const Keys button, const std::function<void(void)>& func);
		of::common::uuid on(const InputStateType messageType, const GamePadButton button, const std::function<void(void)>& func);

		void removeBind(const of::common::uuid& bindId);

	private:

		size_t sentToCorrectChannel(const courier::Message& msg);
		
		GamePadChannel gamePadChannel;
		MouseChannel mouseChannel;
		KeyboardChannel keyboardChannel;

	};

}
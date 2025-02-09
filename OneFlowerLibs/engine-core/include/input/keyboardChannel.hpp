#pragma once

#include <courier/message.hpp>
#include <input/inputEvents.hpp>
#include <input/inputFunctionBind.hpp>

#include <map>

namespace of::input
{
	class KeyboardChannel
	{
	public:
		KeyboardChannel();

		size_t handleInputMessage(const courier::Message& message);

		of::common::uuid on(const InputStateType typ, const of::input::Keys button, const RegularInputBind& bind);

		void removeBind(const of::input::Keys button, const of::common::uuid& bindId);

		void moveBind(const of::input::Keys oldButton, const of::input::Keys newButton);

	private:

		size_t sendPressMessage(const courier::Message& pressMessage);
		size_t sendHoldMessage(const courier::Message& holdsMessage);
		size_t sendReleaseMessage(const courier::Message& releasesMessage);

		std::map<of::input::Keys, std::vector<RegularInputBind>> keyboardButton_Press;
		std::map<of::input::Keys, std::vector<RegularInputBind>> keyboardButton_Hold;
		std::map<of::input::Keys, std::vector<RegularInputBind>> keyboardButton_Release;

	};
}
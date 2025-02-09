#pragma once

#include <courier/message.hpp>
#include <input/inputEvents.hpp>
#include <input/inputFunctionBind.hpp>

#include <map>

namespace of::input
{
	class MouseChannel
	{
	public:
		MouseChannel();

		size_t handleInputMessage(const courier::Message& message);

		of::common::uuid on(const InputStateType typ, const of::input::Mouse button, const RegularInputBind& bind);

		void removeBind(const of::common::uuid& bindId);
		void removeBind(const of::input::Mouse button, const of::common::uuid& bindId);

		void moveBind(const of::input::Mouse oldButton, const of::input::Mouse newButton);

	private:

		size_t sendPressMessage(const courier::Message& pressMessage);
		size_t sendHoldMessage(const courier::Message& holdsMessage);
		size_t sendReleaseMessage(const courier::Message& releasesMessage);

		std::map<of::input::Mouse, std::vector<RegularInputBind>> mouseButton_Press;
		std::map<of::input::Mouse, std::vector<RegularInputBind>> mouseButton_Hold;
		std::map<of::input::Mouse, std::vector<RegularInputBind>> mouseButton_Release;

	};
}
#pragma once

#include <courier/message.hpp>
#include <input/inputEvents.hpp>
#include <input/inputFunctionBind.hpp>

#include <map>

namespace of::input
{
	class GamePadChannel
	{
	public:
		GamePadChannel();

		size_t sendAxisMessage(const courier::Message& axisMessage);
		size_t handleInputMessage(const courier::Message& message);

		of::common::uuid on(const of::input::GamePadAxis axis, const AxisInputBind& bind);
		of::common::uuid on(const InputStateType typ, const of::input::GamePadButton button, const RegularInputBind& bind);

		void removeBind(const of::common::uuid& bindId);
		void removeBind(const of::input::GamePadAxis axis, const of::common::uuid& bindId);
		void removeBind(const of::input::GamePadButton button, const of::common::uuid& bindId);

		void moveBind(const of::input::GamePadAxis oldAxis, const of::input::GamePadAxis newAxis);
		void moveBind(const of::input::GamePadButton oldbutton, const of::input::GamePadButton newAxis);

	private:

		size_t sendPressMessage(const courier::Message& pressMessage);
		size_t sendHoldMessage(const courier::Message& holdMessage);
		size_t sendReleaseMessage(const courier::Message& releaseMessage);

		std::map<of::input::GamePadAxis, std::vector<AxisInputBind>> axisKeybinds;
		std::map<of::input::GamePadButton, std::vector<RegularInputBind>> gamePadButton_Press;
		std::map<of::input::GamePadButton, std::vector<RegularInputBind>> gamePadButton_Hold;
		std::map<of::input::GamePadButton, std::vector<RegularInputBind>> gamePadButton_Release;

	};
}
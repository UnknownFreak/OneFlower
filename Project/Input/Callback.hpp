#ifndef Callback_HPP
#define Callback_HPP

#include <swizzle/core/Input.hpp>

#include <Helpers\String.hpp>
#include <functional>

namespace Input::Callback
{

	template<class Targ, class InputEnum>
	struct Callback
	{
		std::function<void(Targ, InputEnum, const float&)> callbackMethod;
		Core::String callbackName;
		bool callIfRemoved;

		Callback(const Core::String& callbackName, std::function<void(Targ, InputEnum, const float&)> callbackMethod, bool callIfRemoved=false) : callbackName(callbackName), callbackMethod(callbackMethod),
			callIfRemoved(callIfRemoved)
		{
		}
		Callback(const Callback & copy) : callbackName(copy.callbackName), callbackMethod(copy.callbackMethod),
			callIfRemoved(copy.callIfRemoved)
		{
		}
		Callback(const Callback && rval_copy) : callbackName(rval_copy.callbackName), callbackMethod(rval_copy.callbackMethod),
			callIfRemoved(rval_copy.callIfRemoved)
		{
		}
		Callback(const Core::String& callbackName) : callbackName(callbackName)
		{

		}
		Callback & operator=(const Callback & right)
		{
			callbackName = right.callbackName;
			callbackMethod = right.callbackMethod;
			callIfRemoved = right.callIfRemoved;
			return *this;
		}
		Callback & operator=(const Callback && rval_right)
		{
			callbackName = std::move(rval_right.callbackName);
			callbackMethod = std::move(rval_right.callbackMethod);
			callIfRemoved = std::move(rval_right.callIfRemoved);
			return *this;
		}

		bool operator==(const Callback & right)
		{
			return callbackName == right.callbackName;
		}

		bool operator>(const Callback & right)
		{
			return callbackName > right.callbackName;
		}

		bool operator<(const Callback & right)
		{
			return callbackName < right.callbackName;
		}

		void operator()(const Targ& value, const InputEnum & inputMode, const float& fElapsedTime) const
		{
			callbackMethod(value, inputMode, fElapsedTime);
		}

	};

	//typedef Callback<float, sf::Joystick::Axis> AxisCallback;
	typedef Callback<bool, swizzle::input::KeyAction> KeyboardCallback;
	typedef Callback<bool, swizzle::input::Keys> KeyboardCallbackTemp;
	typedef Callback<bool, swizzle::input::Mouse> MouseCallback;
}

#endif

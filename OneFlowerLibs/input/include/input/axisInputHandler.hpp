#ifndef AxisInputHandler_HPP
#define AxisInputHandler_HPP

#include <functional>

#include <Module/Logger/OneLogger.hpp>

#include "InputHandlerBase.hpp"

namespace Input
{
	template <class T>
	class AxisCallbackholder
	{
		InputHandlerBase<T, float> AxisHandler;

	public:

		inline void update(const float& fElapsedTime)
		{
			AxisHandler.update(fElapsedTime);
		}

		AxisCallbackholder(std::function<float(T)> functionToCheckIfInputIsPressed) :
			AxisHandler(functionToCheckIfInputIsPressed)
		{
		}

		inline void RegisterCallback(Callback::Callback<float, T> callback, T input)
		{
			AxisHandler.RegisterCallback(callback, input);
		}

		inline void removeCallback(T input, of::common::String callbackToRemove)
		{
			AxisHandler.RemoveCallback(input, callbackToRemove);
		}

	};
}

#endif

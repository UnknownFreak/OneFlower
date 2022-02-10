#ifndef AxisInputHandler_HPP
#define AxisInputHandler_HPP

#include <functional>

#include <Module/Logger/OneLogger.hpp>
#include <Helpers\Enum\InputEnum.hpp>
#include <Module\EngineModuleManager.hpp>

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

		inline void removeCallback(T input, Core::String callbackToRemove)
		{
			AxisHandler.RemoveCallback(input, callbackToRemove);
		}

	};
}

#endif

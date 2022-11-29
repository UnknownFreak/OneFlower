#ifndef BaseInputHandler_HPP
#define BaseInputHandler_HPP

#include <functional>
#include <vector>

#include <Module/Logger/OneLogger.hpp>
#include <Helpers\Enum\InputEnum.hpp>
#include <Module\EngineModuleManager.hpp>

#include "Callback.hpp"
#include "InputHandlerBase.hpp"

namespace Input
{
	template <class T>
	class BasicInputHandler
	{

		InputHandlerBase<T, bool> bindsOnRelease;
		InputHandlerBase<T, bool> bindsOnPress;
		InputHandlerBase<T, bool> bindsOnHold;
		std::vector<T> callbackRelease;

	public:

		inline void update(const float& fElapsedTime) 
		{
			auto it = bindsOnPress.binds.begin();
			auto eit = bindsOnPress.binds.end();

			for (; it != eit; ++it)
				if (std::find(callbackRelease.begin(), callbackRelease.end(), it->first) == callbackRelease.end())
					if (bindsOnPress.checkInput(it->first))
					{
						for (size_t i = 0; i < it->second.size(); ++i)
							it->second[i](true, it->first, fElapsedTime);
						callbackRelease.push_back(it->first);
					}

			bindsOnHold.update(fElapsedTime);

			it = bindsOnRelease.binds.begin();
			eit = bindsOnRelease.binds.end();

			for (; it != eit; ++it)
				if (std::find(callbackRelease.begin(), callbackRelease.end(), it->first) == callbackRelease.end())
					if (bindsOnRelease.checkInput(it->first))
						callbackRelease.push_back(it->first);


			for (size_t ii = 0; ii < callbackRelease.size(); /* no increment */)
				if (!bindsOnRelease.checkInput(callbackRelease[ii]))
				{
					it = bindsOnRelease.binds.find(callbackRelease[ii]);
					if (it != bindsOnRelease.binds.end())
						for (size_t i = 0; i < it->second.size(); ++i)
							it->second.at(i)(true, it->first, fElapsedTime);
					callbackRelease.erase(callbackRelease.begin() + ii++);
				}
				else
					++ii;
		}
	
		BasicInputHandler(std::function<bool(T)> functionToCheckIfInputIsPressed) :
			bindsOnRelease(functionToCheckIfInputIsPressed),
			bindsOnPress(functionToCheckIfInputIsPressed),
			bindsOnHold(functionToCheckIfInputIsPressed),
			callbackRelease()
		{
		}

		inline void RegisterCallback(Callback::Callback<bool, T> callback, T input, const Enums::Input::Action actionType)
		{
			if ((int)actionType & (int)Enums::Input::Action::Press)
				bindsOnPress.RegisterCallback(callback, input);
			if ((int)actionType & (int)Enums::Input::Action::Release)
				bindsOnRelease.RegisterCallback(callback, input);
			if ((int)actionType & (int)Enums::Input::Action::Hold)
				bindsOnHold.RegisterCallback(callback, input);
		}

		inline void removeCallback(T input, of::common::String callbackToRemove, const Enums::Input::Action actionType)
		{
			if ((int)actionType & (int)Enums::Input::Action::Press)
				if(bindsOnPress.RemoveCallback(input, callbackToRemove))
				{
					typename std::vector<T>::iterator it = std::find(callbackRelease.begin(), callbackRelease.end(), input);
					if (it != callbackRelease.end())
						callbackRelease.erase(it);
				}
			if ((int)actionType & (int)Enums::Input::Action::Release)
				bindsOnRelease.RemoveCallback(input, callbackToRemove);
			if ((int)actionType & (int)Enums::Input::Action::Hold)
				bindsOnHold.RemoveCallback(input, callbackToRemove);
		}
	
	};
}

#endif

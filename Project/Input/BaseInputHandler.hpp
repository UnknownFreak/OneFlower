#ifndef BaseInputHandler_HPP
#define BaseInputHandler_HPP

#include <functional>
#include <map>
#include <vector>

#include <Logger\Logger.hpp>

#include "InputEnum.hpp"
#include "Callback.hpp"
#include <Core\IEngineResource\EngineResourceManager.hpp>


template <class T>
class BaseCallbackholder
{
	typedef std::vector<Callback> callbackVector;

	typedef std::pair<std::map<T, callbackVector>*, Core::String> holderToStringPair;

	std::map<std::map<T, callbackVector>*, Core::String> holderToStringMap;

	std::function<bool(T)> checkInput;

	void insertIntoHolder(const Callback callback, std::map<T ,callbackVector>& holder, const T input)
	{
		std::map<T, callbackVector>::iterator it = holder.find(input);
		if (it == holder.end())
		{
			callbackVector tempVector;
			tempVector.push_back(callback);
			holder.insert(std::pair<T, callbackVector>(input, tempVector));
		}
		else
			it->second.push_back(callback);
	}

	void removeFromHolder(const Core::String& callbackToRemove, std::map<T, callbackVector>& holder, const T& input)
	{
		std::map<T, callbackVector>::iterator it = holder.find(input);
		if (it == holder.end())
		{
			//Engine::Get<OneLogger>().Warning("Trying to remove callback [" << callbackToRemove << "] from holder [" << *holderToStringMap.at(holder)<<
			//	"] when input type is not even registered.");
		}
		else
		{
			std::vector<Callback>::iterator iit = std::find(it->second.begin(), it->second.end(), Callback(callbackToRemove, [] {}));
			if (iit == it->second.end())
			{
				//Engine::Get<OneLogger>().Warning("Trying to remove callback [" << callbackToRemove << "] from [" << *holderToStringMap.at(holder) << "] with input value ["
				//	<< input << "] but it was not found in the vector for that input value.")
			}
			else
			{
				if (iit->callIfRemoved && checkInput(input))
				{
					Callback& c = *iit;
					c();
				}
				it->second.erase(iit);
			}
		}
	}


public:

	inline void update() 
	{
		std::map<T, callbackVector>::iterator it = bindsOnPress.begin();
		std::map<T, callbackVector>::iterator eit = bindsOnPress.end();

		for (; it != eit; ++it)
			if (std::find(callbackRelease.begin(), callbackRelease.end(), it->first) == callbackRelease.end())
				if (checkInput(it->first))
				{
					for (size_t i = 0; i < it->second.size(); ++i)
						it->second[i]();
					callbackRelease.push_back(it->first);
				}

		it = bindsOnHold.begin();
		eit = bindsOnHold.end();

		for (; it != eit; ++it)
			if (checkInput(it->first))
				for (size_t i = 0; i < it->second.size(); ++i)
					it->second[i]();

		it = bindsOnRelease.begin();
		eit = bindsOnRelease.end();

		for (; it != eit; ++it)
			if (std::find(callbackRelease.begin(), callbackRelease.end(), it->first) == callbackRelease.end())
				if (checkInput(it->first))
					callbackRelease.push_back(it->first);


		for (size_t ii = 0; ii < callbackRelease.size(); /* no increment */)
			if (!checkInput(callbackRelease[ii]))
			{
				it = bindsOnRelease.find(callbackRelease[ii]);
				if (it != bindsOnRelease.end())
					for (size_t i = 0; i < it->second.size(); ++i)
						it->second.at(i)();
				callbackRelease.erase(callbackRelease.begin() + ii++);
			}
			else
				++ii;
	}
	
	BaseCallbackholder(std::function<bool(T)> functionToCheckIfInputIsPressed) : bindsOnRelease(), bindsOnPress(), bindsOnHold(), callbackRelease(),
		checkInput(functionToCheckIfInputIsPressed)
	{
		holderToStringMap.insert(holderToStringPair(&bindsOnRelease, "BindsOnRelease"));
		holderToStringMap.insert(holderToStringPair(&bindsOnPress, "BindsOnPress"));
		holderToStringMap.insert(holderToStringPair(&bindsOnHold, "BindsOnHold"));
	}

	inline void RegisterCallback(Callback callback, T input, const Input::Action actionType)
	{
		if (actionType & Input::Action::Press)
			insertIntoHolder(callback, bindsOnPress, input);
		if (actionType & Input::Action::Release)
			insertIntoHolder(callback, bindsOnRelease, input);
		if (actionType & Input::Action::Hold)
			insertIntoHolder(callback, bindsOnHold, input);
	}

	inline void removeCallback(T input, Core::String callbackToRemove, const Input::Action actionType)
	{
		if (actionType & Input::Action::Press)
			removeFromHolder(callbackToRemove, bindsOnPress, input);
		if (actionType & Input::Action::Release)
			removeFromHolder(callbackToRemove, bindsOnRelease, input);
		if (actionType & Input::Action::Hold)
			removeFromHolder(callbackToRemove, bindsOnHold, input);
	}
	
	std::map<T, callbackVector> bindsOnRelease;
	std::map<T, callbackVector> bindsOnPress;
	std::map<T, callbackVector> bindsOnHold;
	std::vector<T> callbackRelease;

};

#endif

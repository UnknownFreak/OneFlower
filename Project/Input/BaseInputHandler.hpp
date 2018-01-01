#ifndef BaseInputHandler_HPP
#define BaseInputHandler_HPP

#include <functional>
#include <map>
#include <vector>

#include "InputEnum.hpp"

template <class T>
class BaseCallbackholder
{

	void insertIntoHolder(std::function<void(void)> callback, std::map<T,std::vector<std::function<void(void)>>>& holder, T input)
	{
		auto it = holder.find(input);
		if (it == holder.end())
		{
			std::vector<std::function<void(void)>> tempVector;
			tempVector.push_back(callback);
			holder.insert(std::pair<T, std::vector < std::function < void(void)>>>(input, tempVector));
		}
		else
			it->second.push_back(callback);
	}

public:

	inline void update() {
	}

	BaseCallbackholder() :bindsOnRelease(), bindsOnPress(), bindsOnHold(), callbacRelease() { };

	inline void RegisterCallback(std::function<void(void)> callback, T input, Input::Action actionType)
	{
		if (actionType & Input::Action::Press)
		{
			insertIntoHolder(callback, bindsOnPress, input);
		}
		if (actionType & Input::Action::Release)
		{
			insertIntoHolder(callback, bindsOnRelease, input);
		}
		if (actionType & Input::Action::Hold)
		{
			insertIntoHolder(callback, bindsOnHold, input);
		}
	}

	inline void removeCallback(T input, std::function<void(void)> callbackToRemove)
	{
	}

	std::map<T, std::vector<std::function<void(void)>>> bindsOnRelease;
	std::map<T, std::vector<std::function<void(void)>>> bindsOnPress;
	std::map<T, std::vector<std::function<void(void)>>> bindsOnHold;
	std::vector<T> callbackRelease;

};

#endif

#include "Mouse.hpp"

void scrollupdate();
Mouse::Mouse() : pos(0, 0), offset(0, 0)
{
}

void Mouse::update()
{
	for (auto it = bindsOnPress.begin(); it != bindsOnPress.end(); ++it)
		if (std::find(callbackRelease.begin(), callbackRelease.end(), it->first) == callbackRelease.end())
			if (sf::Mouse::isButtonPressed(it->first))
			{
				for (size_t i = 0; i < it->second.size(); ++i)
					it->second[i]();
				callbackRelease.push_back(it->first);
			}
	for (auto it = bindsOnHold.begin(); it != bindsOnHold.end(); ++it)
		if (sf::Mouse::isButtonPressed(it->first))
			for (size_t i = 0; i < it->second.size(); ++i)
				it->second[i]();

	for (auto it = bindsOnRelease.begin(); it != bindsOnRelease.end(); ++it)
		if (std::find(callbackRelease.begin(), callbackRelease.end(), it->first) == callbackRelease.end())
			if (sf::Mouse::isButtonPressed(it->first))
				callbackRelease.push_back(it->first);

	for (size_t ii = 0; ii < callbackRelease.size(); /* no increment */)
		if (!sf::Mouse::isButtonPressed(callbackRelease[ii]))
		{
			std::map<sf::Mouse::Button, std::vector<std::function<void(void)>>>::iterator jit = bindsOnRelease.find(callbackRelease[ii]);
			if (jit != bindsOnRelease.end())
				for (size_t i = 0; i < jit->second.size(); ++i)
					jit->second.at(i)();
			callbackRelease.erase(callbackRelease.begin() + ii++);
		}
		else
			++ii;
}

void Mouse::registerCallback(std::function<void(void)> callback, sf::Mouse::Button button, Input::Action actionType)
{
	if (actionType & Input::Action::Press)
	{
		auto it = bindsOnPress.find(button);
		if (it == bindsOnPress.end())
		{
			std::vector<std::function<void(void)>> tempVector;
			tempVector.push_back(callback);
			bindsOnPress.insert(std::pair<sf::Mouse::Button, std::vector < std::function < void(void)>>>(button, tempVector));
		}
		else
			it->second.push_back(callback);
	}

	if (actionType & Input::Action::Release)
	{
		auto it = bindsOnRelease.find(button);
		if (it == bindsOnRelease.end())
		{
			std::vector<std::function<void(void)>> tempVector;
			tempVector.push_back(callback);
			bindsOnRelease.insert(std::pair<sf::Mouse::Button, std::vector < std::function < void(void)>>>(button, tempVector));
		}
		else
			it->second.push_back(callback);
	}

	if (actionType & Input::Action::Hold)
	{
		auto it = bindsOnHold.find(button);

		if (it == bindsOnHold.end())
		{
			std::vector<std::function<void(void)>> tempVector;
			tempVector.push_back(callback);
			bindsOnHold.insert(std::pair<sf::Mouse::Button, std::vector < std::function < void(void)>>>(button, tempVector));
		}
		else
			it->second.push_back(callback);
	}
}
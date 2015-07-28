#include "InputHandler.hpp"
#include <SFML\Window\Event.hpp>
#include "Engine.hpp"
#include <functional>
//LOW: Probably not needed, if re-designing the architect, For the vector find
#include <algorithm>
void InputHandler::update()
{
	mouse.update();
	for(auto it = bindsOnPress.begin(); it != bindsOnPress.end(); ++it)
		if(std::find(callbackRelease.begin(),callbackRelease.end(),it->first) == callbackRelease.end())
			if(sf::Keyboard::isKeyPressed(it->first))
			{
				for(size_t i = 0; i < it->second.size(); ++i)
					it->second[i]();
				callbackRelease.push_back(it->first);
			}

	for(auto it = bindsOnRelease.begin(); it != bindsOnRelease.end(); ++it)
		if(std::find(callbackRelease.begin(),callbackRelease.end(),it->first) == callbackRelease.end())
			if(sf::Keyboard::isKeyPressed(it->first))
				callbackRelease.push_back(it->first);

	for(auto i = 0; i < callbackRelease.size(); /* no increment */)
		if(!sf::Keyboard::isKeyPressed(callbackRelease[i]))
		{
			std::map<sf::Keyboard::Key,std::vector<std::function<void(void)>>>::iterator jit = bindsOnRelease.find(callbackRelease[i]);
			if(jit != bindsOnRelease.end())
				for(size_t i = 0; i < jit->second.size(); ++i)
					jit->second.at(i)();
			callbackRelease.erase(callbackRelease.begin()+i++);
		}
		else
			++i;


	//[DONE] 25/06/15 
	//LOW: Make it so that callback is inside a vector, to reduce the need to recheck if the same key condition is correct,	
	//if(true)//Engine::event.type == sf::Event::KeyPressed)
	//if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	//{
	//	for(auto it = bindsOnControl.begin(); it != bindsOnControl.end(); ++it)
	//		if(sf::Keyboard::isKeyPressed(it->first))
	//			for(auto i = 0; i < it->second.size(); ++i)
	//				it->second[i]();
	//}
	//else
	//{
	//	//std::map<sf::Keyboard::Key,std::vector<std::function<void(void)>>>::iterator
	//	for(auto it = bindsOnPress.begin(); it != bindsOnPress.end(); ++it)
	//		if(sf::Keyboard::isKeyPressed(it->first))
	//			if(callbackRelease.find(it->first) == callbackRelease.end())
	//				for(auto i = 0; i < it->second.size(); ++i)
	//				{
	//					it->second[i]();
	//					callbackRelease.insert(std::make_pair(it->first,&it->second));
	//				}
	//	
	//	/*for(auto it = bindsOnRelease.begin(); it != bindsOnRelease.end(); ++it)
	//		if(sf::Keyboard::isKeyPressed(it->first))
	//			for(auto i = 0; i < it->second.size(); ++i)
	//				callbackRelease.insert(std::make_pair(it->first,&it->second));
	//	//*/
	//	std::vector<std::map<sf::Keyboard::Key,std::vector<std::function<void(void)>>*>::iterator> remove;
	//	for(auto it = callbackRelease.begin(); it != callbackRelease.end(); ++it)
	//		if(!sf::Keyboard::isKeyPressed(it->first))
	//		{
	//			for(auto i = 0; i < it->second->size(); ++i)
	//				it->second->at(i)();
	//			remove.push_back(it);
	//		}
	//		//*/
	//	for(auto it = remove.begin(); it != remove.end(); ++it)
	//		callbackRelease.erase(*it);
	//}
}

void InputHandler::registerCallback(std::function<void(void)> callback,sf::Keyboard::Key key,Input::Action actionType)
{

	if(actionType & Input::Action::Press)
	{
		auto it = bindsOnPress.find(key);
		if(it == bindsOnPress.end())
		{
			std::vector<std::function<void(void)>> tempVector;
			tempVector.push_back(callback);
			bindsOnPress.insert(std::pair<sf::Keyboard::Key,std::vector < std::function < void(void)>>>(key,tempVector));
		}
		else
			it->second.push_back(callback);
	}

	if(actionType & Input::Action::Release)
	{
		auto it = bindsOnRelease.find(key);
		if(it == bindsOnRelease.end())
		{
			std::vector<std::function<void(void)>> tempVector;
			tempVector.push_back(callback);
			bindsOnRelease.insert(std::pair<sf::Keyboard::Key,std::vector < std::function < void(void)>>>(key,tempVector));
		}
		else
			it->second.push_back(callback);
	}

	if(actionType & Input::Action::Hold)
	{
		
	}
}



/*
void InputHandler::onControlPress(std::function<void(void)> callback,sf::Keyboard::Key key)
{
	auto it = bindsOnControl.find(key);
	if(it == bindsOnControl.end())
	{
		std::vector<std::function<void(void)>> tempVector;
		tempVector.push_back(callback);
		bindsOnControl.insert(std::pair<sf::Keyboard::Key,std::vector < std::function < void(void)>>>(key,tempVector));
	}
	else
		it->second.push_back(callback);
}


void InputHandler::onKeyPress(CallBack callback,sf::Keyboard::Key key)
{
	auto it = bindsOnPress.find(key);
	if(it == bindsOnPress.end())
	{
		std::vector<std::function<void(void)>> tempVector;
		tempVector.push_back(callback);
		bindsOnPress.insert(std::pair<sf::Keyboard::Key,std::vector < std::function < void(void)>>>(key,tempVector));
	}
	else
		it->second.push_back(callback);
}
void InputHandler::onKeyRelease(CallBack callback,sf::Keyboard::Key key)
{
	auto it = bindsOnRelease.find(key);
	if(it == bindsOnRelease.end())
	{
		std::vector<std::function<void(void)>> tempVector;
		tempVector.push_back(callback);
		bindsOnRelease.insert(std::pair<sf::Keyboard::Key,std::vector < std::function < void(void)>>>(key,tempVector));
	}
	else
		it->second.push_back(callback);
}
//*/
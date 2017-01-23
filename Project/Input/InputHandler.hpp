#ifndef InputHandler_HPP_A
#define InputHandler_HPP_A

#include <map>
#include <string>
#include <vector>
#include <SFML\Window\Keyboard.hpp>
#include "Mouse.hpp"
#include <functional>
#include "InputEnum.hpp"
/*
template<typename returnType,typename parameterType>
class EventType : EventTypeBase
{
public:
returnType(*callback)(parameterType);
private:
};

class EventTypeBase
{
public:
EventTypeBase();

CallBack callback;
};

class EventSystem
{
public:
std::map<std::string,std::vector<CallBack>> events;
void add(std::string,void(void));
private:

#ifdef _DEBUG

#endif
};
//*/
typedef void(*CallBack)(void);

class InputHandler
{
public:
	void update();
	void registerCallback(std::function<void(void)> callbk, sf::Keyboard::Key key, Input::Action);

	Mouse mouse;
private:
	std::map<sf::Keyboard::Key, std::vector<std::function<void(void)>>> bindsOnPress;
	std::map<sf::Keyboard::Key, std::vector<std::function<void(void)>>> bindsOnRelease;
	std::map<sf::Keyboard::Key, std::vector<std::function<void(void)>>> bindsOnHold;
	std::map<sf::Keyboard::Key, std::vector<std::function<void(void)>>> bindsOnControl;
	std::vector<sf::Keyboard::Key> callbackRelease;

	/*
	void onKeyPress(CallBack type,sf::Keyboard::Key key);
	void onKeyRelease(CallBack type,sf::Keyboard::Key key);
	void onControlPress(std::function<void(void)>,sf::Keyboard::Key key);
	//*/
};

#endif
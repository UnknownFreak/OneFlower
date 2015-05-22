#ifndef InputHandler_HPP_A
#define InputHandler_HPP_A

#include <map>
#include <string>
#include <vector>
#include <SFML\Window\Keyboard.hpp>
#include "Mouse\Mouse.hpp"

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
typedef void (*CallBack)(void);

class InputHandler
{
public:
	void update();
	void addKeybind(sf::Keyboard::Key key,CallBack type);
	Mouse mouse;
private:
	std::map<sf::Keyboard::Key,CallBack> keybinds;

};






#endif
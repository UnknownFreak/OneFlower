#ifndef InputHandler_HPP_A
#define InputHandler_HPP_A

#include <functional>
#include <map>
#include <vector>

#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include "InputEnum.hpp"

#include <Core\EngineModule\IEngineModule.hpp>

#include "BaseInputHandler.hpp"

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

class InputHandler : public IEngineResource<InputHandler>
{
public:
	void update();

	BaseCallbackholder<sf::Keyboard::Key> keyboard;
	BaseCallbackholder<sf::Mouse::Button> mouse;

	const ResourceType& getType()
	{
		return type;
	}

	InputHandler();

	int deltaScrolls = 0;

private:

	/*
	void onKeyPress(CallBack type,sf::Keyboard::Key key);
	void onKeyRelease(CallBack type,sf::Keyboard::Key key);
	void onControlPress(std::function<void(void)>,sf::Keyboard::Key key);
	//*/
};

#endif
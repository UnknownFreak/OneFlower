#ifndef MESSAGEDEFINER_HPP
#define MESSAGEDEFINER_HPP
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\System\Clock.hpp>
#include <cereal\access.hpp>

class Message
{
public:
	/*
	Variables
	//*/
	sf::Font font;
	sf::Clock timer;
	sf::Color color;
	sf::Text text;
	int size;
	int maxLength;
	int marginWidth;
	float duration;
	/*
	Constructor / deconstructor
	//*/

	Message();
	Message(sf::Font& font, float dur = -1, int length = -1);
	//Message(Message& msg);
	virtual ~Message();

	/*
	Functions
	//*/

	void setFont(sf::Font* font);
	void setColor(sf::Color c);
	void setSize(int s);
	void setMarginWidth(int w);
	void setLength(int l);
	
	virtual void move(int x, int y);
	virtual void move(float x, float y);
	virtual void setPosition(int x, int y);
	virtual void setPosition(float x, float y);

	Message& operator=(std::string s);

	virtual void drawMessage(sf::RenderWindow* rwd);
private:

	template <class Archive>//, GameObject& go>
	friend void save(Archive& archive, const Message& msg);
	template <class Archive>//, GameObject& go>
	friend void load(Archive& archive, Message& msg);
};
#endif MESSAGEDEFINER_HPP
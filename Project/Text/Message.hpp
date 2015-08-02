#ifndef MESSAGE_HPP
#define MESSAGE_HPP
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
	sf::Text entireString;
	std::vector<std::pair<sf::Text, bool>> text;
	int size;
	int maxLength;
	int marginWidth;
	double duration;
	/*
	Constructor / deconstructor
	//*/

	Message();
	Message(const sf::Font& font,const double dur = -1,const int length = -1);
	Message(const Message& msg);
	virtual ~Message() = default;

	/*
	Functions
	//*/
	virtual void draw();
	virtual void drawCrop(sf::IntRect area);

	void setFont(sf::Font* font);
	void setColor(sf::Color c);
	void setSize(int s);
	void setMarginWidth(int w);
	void setLength(int l);
	
	virtual void move(double x, double y);
	virtual void setPosition(double x, double y);

	Message& operator=(std::string s);
	//Message& operator+=(std::string s);
	
	virtual const std::string getString();
	
protected:

	void createBody(std::string s);
	virtual int iconFormat(std::pair<sf::Text, bool>& pair,std::vector<std::string>& iit, int iterpos);

private:

	template <class Archive>//, GameObject& go>
	friend void save(Archive& archive, const Message& msg);
	template <class Archive>//, GameObject& go>
	friend void load(Archive& archive, Message& msg);
};
#endif Message_HPP

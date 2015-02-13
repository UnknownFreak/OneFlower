#ifndef FLOATINGTEXT_HPP
#define FLOATINGTEXT_HPP

#include "Message.hpp"
#include <string>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics.hpp>
#include <exception>
class FloatingText : public Message
{
public:
	
	/*
	Variables
	//*/
	std::string iconName;
	sf::Sprite iconSprite;


	/*
	Constructor
	//*/
	FloatingText(std::string iconName, sf::Font& font, double duration = 3, int len = -1, int offsetX = 0, int offsetY = 0);
	FloatingText(FloatingText& ft);
	FloatingText();
	virtual ~FloatingText();
	/*
	Functions
	//*/
	void move(int x, int y);
	void move(float x, float y);
	void setPosition(int x, int y);
	void setPosition(float x, float y);
	void setIcon(std::string name);
	void drawMessage(sf::RenderWindow* rw);
	void setOffset(int x, int y);
	FloatingText& operator=(std::string info);

protected:
	int offsetX;
	int offsetY;
private:
	template<class Archive>
	friend void save(Archive& ar, const FloatingText& ft);
	template<class Archive>
	friend void load(Archive& ar, FloatingText& ft);
};

class MissingIconException : public std::exception
{
	sf::Sprite tmp;
public:
	MissingIconException(sf::Sprite& sprite);
//	~MissingIconException(void);
	const sf::Texture* what();

};

#endif
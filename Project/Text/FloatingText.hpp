#ifndef FLOATINGTEXT_HPP
#define FLOATINGTEXT_HPP

#include "Message.hpp"
#include <string>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics.hpp>
#include <exception>
#include "../Vector.h"

class FloatingText: public Message
{
public:

	/*
	Variables
	//*/
	std::string iconName;
	sf::Sprite iconSprite;
	Vector2 offset;
	/*
	Constructor
	//*/
	FloatingText(std::string iconName,sf::Font& font,double duration = 3,int len = -1,int offsetX = 0,int offsetY = 0);
	FloatingText(const FloatingText& ft);
	FloatingText();
	virtual ~FloatingText();
	/*
	Functions
	//*/
	void move(double x,double y);
	void setPosition(double x,double y);
	void setIcon(std::string name);
	void drawMessage(sf::RenderWindow* rw);
	void setOffset(double x,double y);
	FloatingText& operator=(std::string info);

protected:

private:
	template<class Archive>
	friend void save(Archive& ar,const FloatingText& ft);
	template<class Archive>
	friend void load(Archive& ar,FloatingText& ft);
};

class MissingIconException: public std::exception
{
	sf::Sprite tmp;
public:
	MissingIconException(sf::Sprite& sprite);
	//	~MissingIconException(void);
	const sf::Texture* what();
};

#endif
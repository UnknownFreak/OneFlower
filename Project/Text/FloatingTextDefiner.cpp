#include "FloatingText.hpp"
#include "../Gfx.h"
#include "../Engine.hpp"


FloatingText::FloatingText() : Message(*Engine::Graphic.font.requestFont("Arial.ttf"), -1, -1), offset(0, 0), iconName(""), drawIcon(true)
{
	iconSprite.setTexture(*Engine::Graphic.requestTexture("test.png"),true);
	createBody("");
}
FloatingText::FloatingText(std::string icoName, sf::Font& f, bool drawIcon, double dur, int l, int oX, int oY) : Message(f, dur, l), offset(oX, oY), iconName(icoName), drawIcon(drawIcon)
{
	createBody("");
	setIcon(iconName);
}
FloatingText::FloatingText(const FloatingText& ft) : Message(ft.font, ft.duration, ft.maxLength), offset(ft.offset), iconName(ft.iconName), drawIcon(ft.drawIcon)
{
	setColor(ft.color);
	createBody(ft.entireString.getString());
	if (ft.text.size() != 0)
		setPosition(ft.text[0].first.getPosition().x, ft.text[0].first.getPosition().y);
	setIcon(iconName);
}
void FloatingText::draw()
{
	if (drawIcon)
		Engine::View.render.draw(iconSprite);
	for (std::map<int, std::pair<sf::Sprite, Vector2>>::iterator it = icons.begin(); it != icons.end(); it++)
		Engine::View.render.draw(it->second.first);
	Message::draw();
}
void FloatingText::move(double x,double y)
{
	Message::move(x,y);
	for (std::map<int, std::pair<sf::Sprite, Vector2>>::iterator it = icons.begin(); it != icons.end(); it++)
		it->second.first.move(x,y);
	iconSprite.move(x,y);
}

void FloatingText::setPosition(double x,double y)
{
	Message::setPosition(x + offset.x,y + offset.y);
	for (std::map<int, std::pair<sf::Sprite, Vector2>>::iterator it = icons.begin(); it != icons.end(); it++)
	{
		if (text[it->first].second)
		{
			std::map<int, std::pair<sf::Sprite, Vector2>>::iterator before = it;
			before--;
			text[it->first].first.setPosition(before->second.first.getPosition().x + before->second.first.getLocalBounds().width, before->second.first.getPosition().y);
		}
		it->second.first.setPosition(text[it->first].first.getPosition().x + it->second.second.x, text[it->first].first.getPosition().y + it->second.second.y);
	}
	iconSprite.setPosition(x, y);
}
void FloatingText::setOffset(double x,double y)
{
	offset.x = x;
	offset.y = y;
}

FloatingText& FloatingText::operator=(std::string info)
{
	if (this)
	{
		if (info.length() > maxLength && maxLength > 0)
		{
			info.resize(maxLength);
		}
		if (info != entireString.getString())
			icons.clear();
		createBody(info);
	}
	return *this;
}
void FloatingText::setIcon(std::string name)
{
	iconName = name;
	if(!Engine::Graphic.loadTexture(iconName))
#ifdef _DEBUG
		throw MissingIconException(this->iconSprite);
#else
	{
		//LOW set propper missingtexture
		icoName = "test.png";
		iconSprite.setTexture(*Engine::Graphic.requestTexture(icoName),true);
	}
#endif
	else
	{
		iconSprite.setTexture(*Engine::Graphic.requestTexture(iconName),true);
	}
}
int FloatingText::iconFormat(std::pair<sf::Text, bool>& pair,std::vector<std::string>& iit, int iterpos)
{
	
	if (iit[iterpos + 1] == "coins")
	{
		sf::Sprite tmp(*Engine::Graphic.requestTexture(iit[iterpos + 1] + ".png"));
		
		std::string str = iit[iterpos + 4];
		if (str.size() > 4)
		{
			tmp.setTextureRect(sf::IntRect(0, 0, 16, 16));
			icons.insert(std::pair<int,std::pair<sf::Sprite,Vector2>>(text.size(),
			std::pair<sf::Sprite, Vector2>(tmp, Vector2(std::stoi(iit[iterpos + 2]), std::stoi(iit[iterpos + 3])))));

			std::string first = str.substr(0, str.size() - 4);
			std::string second = str.substr(str.size() - 4, 2);
			std::string third = str.substr(str.size() - 2, 2);
			pair.first.setColor(sf::Color(237, 200, 0));
			pair.first.setString(first);
			text.push_back(pair);


			pair.first.setColor(sf::Color(206, 199, 178));
			pair.second = true;

			if (second[0] != '0')
				pair.first.setString(second);
			else if (second[0] == '0' && second[1] == '0')
				pair.first.setString("0");
			else
			{
				second.erase(0, 1);
				pair.first.setString(second);
			}
			tmp.setTextureRect(sf::IntRect(16, 0, 16, 16));
			icons.insert(std::pair<int, std::pair<sf::Sprite, Vector2>>(text.size(),
			std::pair<sf::Sprite, Vector2>(tmp, Vector2(std::stoi(iit[iterpos + 2]), std::stoi(iit[iterpos + 3])))));
			text.push_back(pair);

			pair.first.setColor(sf::Color(109, 43, 5));
			if (str[str.size() - 2] != '0')
				pair.first.setString(str.substr(str.size() - 2));
			else if (str[str.size() - 2] != '0' && str[str.size() - 1] != '0')
				pair.first.setString("0");
			else
				pair.first.setString(str.substr(str.size() - 1));
				
			tmp.setTextureRect(sf::IntRect(32, 0, 16, 16));
			icons.insert(std::pair<int, std::pair<sf::Sprite, Vector2>>(text.size(), 
			std::pair<sf::Sprite, Vector2>(tmp, Vector2(std::stoi(iit[iterpos + 2]), std::stoi(iit[iterpos + 3])))));
		
			text.push_back(pair);
			pair.second = false;
		}
		else if (str.size() > 2)
		{
			pair.first.setColor(sf::Color(206, 199, 178));
			if (str.size() == 4)
				pair.first.setString(str.substr(0, str.size() - 2));
			else
				pair.first.setString(str.substr(0, 1));
			
			tmp.setTextureRect(sf::IntRect(16, 0, 16, 16));
			icons.insert(std::pair<int, std::pair<sf::Sprite, Vector2>>(text.size(),
			std::pair<sf::Sprite, Vector2>(tmp, Vector2(std::stoi(iit[iterpos + 2]), std::stoi(iit[iterpos + 3])))));

			text.push_back(pair);
			pair.second = true;

			pair.first.setColor(sf::Color(109, 43, 5));
			tmp.setTextureRect(sf::IntRect(32, 0, 16, 16));
			icons.insert(std::pair<int, std::pair<sf::Sprite, Vector2>>(text.size(), 
			std::pair<sf::Sprite, Vector2>(tmp, Vector2(std::stoi(iit[iterpos + 2]), std::stoi(iit[iterpos + 3])))));
			
			if (str[str.size() - 2] != '0')
				pair.first.setString(str.substr(str.size() - 2));
			else
				pair.first.setString(str.substr(str.size() - 1));
			text.push_back(pair);
			pair.second = false;
		}
		else
		{
			pair.first.setColor(sf::Color(109, 43, 5));
			pair.first.setString(str);
			tmp.setTextureRect(sf::IntRect(32, 0, 16, 16));
			icons.insert(std::pair<int, std::pair<sf::Sprite, Vector2>>(text.size(), 
			std::pair<sf::Sprite, Vector2>(tmp, Vector2(std::stoi(iit[iterpos + 2]), std::stoi(iit[iterpos + 3])))));
			text.push_back(pair);
		}
		iterpos += 4;
	}
	else
	{
		icons.insert(std::pair<int, std::pair<sf::Sprite, Vector2>>(text.size()
			, std::pair<sf::Sprite, Vector2>(sf::Sprite(*Engine::Graphic.requestTexture(iit[iterpos + 1] + ".png")), 
			Vector2(std::stoi(iit[iterpos + 2]), std::stoi(iit[iterpos + 3])))));
		if (iit[iterpos + 4] == "false")
			pair.second = false;
		else pair.second = true;
		pair.first.setString(iit[iterpos + 5]);
		text.push_back(pair);
		iterpos += 5;
	}
	return iterpos;
}

MissingIconException::MissingIconException(sf::Sprite& sprite)
{
	tmp.setTexture(*Engine::Graphic.requestTexture("test.png"));
}

const sf::Texture* MissingIconException::what()
{
	return tmp.getTexture();
}

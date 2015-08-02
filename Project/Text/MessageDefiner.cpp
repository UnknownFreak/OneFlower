#include "Message.hpp"
#include "Font.hpp"
#include <string>
#include "../Engine.hpp"
#include "../Component/EquipmentComponent.hpp"
#include "../Item/Armor.hpp"
Message::Message(const Message& msg) :text(msg.text), color(msg.color), size(msg.size), duration(msg.duration), maxLength(msg.maxLength), font(msg.font), entireString("",font,size)
{
	for (size_t it = 0; it < text.size(); it++)
		text[it].first.setFont(font);
}
Message::Message() : text(), color(sf::Color::Black), size(30), duration(5), maxLength(-1), entireString()
{
}
Message::Message(const sf::Font& f, const double dur, const int length) : text(), font(f), color(sf::Color::Black), size(30), duration(dur), maxLength(length), entireString("",font,size)
{
}
void Message::move(double offsetX,double offsetY)
{
	if (offsetX != 0 || offsetY != 0)
	for (std::vector<std::pair<sf::Text, bool>>::iterator it = text.begin(); it != text.end(); it++)
		it->first.move(offsetX,offsetY);
}
Message& Message::operator=(std::string s)
{
	if(s.length() > maxLength && maxLength > 0)
	{
		s.resize(maxLength);
	}
	if (s != entireString.getString())
		createBody(s);
	return *this;
}
void Message::setColor(sf::Color c)
{
	color = c;
	for (std::vector<std::pair<sf::Text, bool>>::iterator it = text.begin(); it != text.end(); ++it)
		it->first.setColor(c);
}
void Message::setSize(int s)
{
	if (size != s)
	{
		size = s;
		entireString.setCharacterSize(size);
		for (std::vector<std::pair<sf::Text, bool>>::iterator it = text.begin(); it != text.end(); ++it)
			it->first.setCharacterSize(size);
	}
}
void Message::setLength(int l)
{
	std::string tmp = "";
	maxLength = l;
	if(l > 0)
	{
		for (std::vector<std::pair<sf::Text, bool>>::iterator it = text.begin(); it != text.end(); ++it)
			tmp += it->first.getString();
		tmp.resize(l);
		createBody(tmp);
		entireString.setString(tmp);
	}
}
void Message::setPosition(double x,double y)
{
	int i = 0;
	if (text.size() != 0)
		if (x != text[0].first.getPosition().x || y != text[0].first.getPosition().y)
			for (std::vector<std::pair<sf::Text, bool>>::iterator it = text.begin(); it != text.end(); ++it)
			{
				if (it->second)
				{
					std::vector<std::pair<sf::Text, bool>>::iterator before = it;
					if(text.size() > 1)
						--before;
					--i;
					it->first.setPosition(before->first.getPosition().x + before->first.getLocalBounds().width, y + 16 * i);
					++i;
				}
				else
				{
					it->first.setPosition(x, y + 16 * i);
					++i;
				}
			}
}
void Message::draw()
{

for (std::vector<std::pair<sf::Text, bool>>::iterator it = text.begin(); it != text.end(); ++it)
		Engine::Graphic.view.render.draw(it->first);
}

void Message::drawCrop(sf::IntRect area)
{
	for (std::vector<std::pair<sf::Text, bool>>::iterator it = text.begin(); it != text.end(); ++it)
	{
		if (it->first.getPosition().y > area.top && it->first.getPosition().y + it->first.getGlobalBounds().height < area.top + area.height)
			Engine::Graphic.view.render.draw(it->first);
		else if (it->first.getPosition().y + it->first.getGlobalBounds().height > area.top && !(it->first.getPosition().y + it->first.getGlobalBounds().height > area.top + area.height))
			Engine::Graphic.view.render.draw(it->first);
		else if (it->first.getPosition().y < area.top + area.height && it->first.getPosition().y + it->first.getGlobalBounds().height > area.top + area.height)
			Engine::Graphic.view.render.draw(it->first);
	}
}
void Message::setFont(sf::Font* font)
{
	if(font == NULL)
#ifdef _DEBUG
		throw MissingFontException();
#else
		//LOW set propper misingFontt
		this->font = Engine::Graphic.font.requestFont("arial.ttf");
#endif

	this->font = *font;
	entireString.setFont(*font);
	for (std::vector<std::pair<sf::Text, bool>>::iterator it = text.begin(); it != text.end(); ++it)
		it->first.setFont(*font);
}

const std::string Message::getString()
{
	return entireString.getString();
}

void Message::createBody(std::string s)
{
	if (s != entireString.getString())
	{
		entireString.setString(s);
		text.clear();
		std::vector<std::string> lines;
		std::stringstream ss(s);
		std::string item;
		//split text by rows - rework this 
		while (std::getline(ss, item, '\n'))
			lines.push_back(item);

		std::vector<std::string> elems;
		for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
		{
			std::stringstream ss(*it);
			while (std::getline(ss, item, '§'))
			{
				if (item != "")
					elems.push_back(item);
			}
		}
		sf::Text msg("", *Engine::Graphic.font.requestFont("Arial.ttf"), size);
		msg.setColor(color);
		std::pair<sf::Text, bool> pair(msg, false);
		for (std::vector<std::string>::iterator it = elems.begin(); it != elems.end(); ++it)
		{
			std::string tmp = *it;
			int i = tmp.find("|");
			if (i > 0)
			{
				std::vector<std::string> substr;
				std::stringstream ss(tmp);
				std::string item;
				std::string plusMinus;
				while (std::getline(ss, item, '|'))
					substr.push_back(item);
				for (size_t iit = 0; iit < substr.size(); iit++)
				{
					if (substr[iit] == "Color")
					{
						int r = std::stoi(substr[iit + 1]);
						int g = std::stoi(substr[iit + 2]);
						int b = std::stoi(substr[iit + 3]);
						pair.first.setString(substr[iit + 4]);
						pair.first.setColor(sf::Color(r, g, b));
						text.push_back(pair);
						pair.first.setColor(color);
						iit += 4;
					}
					else if (substr[iit] == "sColor")
					{
						int r = std::stoi(substr[iit + 1]);
						int g = std::stoi(substr[iit + 2]);
						int b = std::stoi(substr[iit + 3]);
						pair.first.setString(substr[iit + 4]);
						pair.second = true;
						pair.first.setColor(sf::Color(r, g, b));
						text.push_back(pair);
						pair.first.setColor(color);
						pair.second = false;
						iit += 4;
					}
					else if (substr[iit] == "Compare")
#pragma region compare
					{
						std::string compType = substr[iit + 1] + substr[iit + 3];
						if (compType == "is-i")
						{
						#pragma region int-intCompare
						int first = std::stoi(substr[iit + 2]);
						int second = 0; 
						GameObject* go = Engine::Window.focus.gameObject;
						if (go)
						{
							EquipmentComponent* ecp = go->GetComponent<EquipmentComponent>();
							if (ecp)
								if (substr[iit + 4] == "Helm")
									if (ecp->helm)
										second = ecp->helm->defense;
									else if (substr[iit + 4] == "Chest")
									if (ecp->chest)
										second = ecp->chest->defense;
									else if (substr[iit + 4] == "Gloves")
									if (ecp->gloves)
										second = ecp->gloves->defense;
									else if (substr[iit + 4] == "Leggings")
									if (ecp->leggings)
										second = ecp->leggings->defense;
									else if (substr[iit + 4] == "Boots")
									if (ecp->boots)
										second = ecp->boots->defense;
						}
						int split = first - second;
						if (split < 0)
							{
								plusMinus = " ";
								pair.first.setColor(sf::Color(150, 25, 25));
							}
							else if (split > 0)
							{
								plusMinus = " +";
								pair.first.setColor(sf::Color(25, 150, 25));
							}
							else
							{
								plusMinus = " ";
								pair.first.setColor(sf::Color(color));
							}
							if (split != 0)
								pair.first.setString(plusMinus + std::to_string(split));
							else
								pair.first.setString("");
						#pragma endregion
						}
						
						pair.second = true;
						text.push_back(pair);

						pair.second = false;
						iit += 4;
					}
#pragma endregion
					else if (substr[iit] == "Icon")
					{
						iit = iconFormat(pair,substr,iit);
					}
				}
			}
			else
			{
				pair.first.setColor(sf::Color(color));
				pair.first.setString(*it);
				text.push_back(pair);
			}
		}
	}
}
int Message::iconFormat(std::pair<sf::Text, bool>& pair,std::vector<std::string>& iit, int iterpos)
{
	return iterpos;
}
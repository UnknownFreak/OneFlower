#ifndef FONTDEFINER_HPP
#define FONTDEFINER_HPP
#include "MessageDefiner.hpp"
#include "SFML\Graphics\Font.hpp"
#include <string>
#include <map>

class Font
{
public:
	std::map < std::string, sf::Font > font;
	Font();
	bool loadFont(std::string name);
	sf::Font* requestFont(std::string name);
private:

};
#endif FONTDEFINER_HPP
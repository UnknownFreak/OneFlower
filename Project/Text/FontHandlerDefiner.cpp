#include "FontDefiner.hpp"
#include <Windows.h>
Font::Font() {
	
}
bool Font::loadFont(std::string name) 
{
	sf::Font tmp;
	if (!tmp.loadFromFile(name))
	{
		MessageBox(0, "Error loading from file", name.c_str(),MB_OK);
		return false;
	}
	font.insert(font.end(), std::make_pair(name, tmp));
	return true;
}

sf::Font* Font::requestFont(std::string name) {
	std::map<std::string, sf::Font>::iterator it;
	it = font.find(name);
	if (it != font.end()) 
		return &it->second;
	if (loadFont(name))
		return &font.find(name)->second;
	return false;
}
#ifndef Font_HPP
#define Font_HPP
#include "SFML\Graphics\Font.hpp"
#include <string>
#include <map>
#include <exception>
	namespace GUI
	{
		class Font
		{
		public:
			std::map < std::string, sf::Font > font;
			Font();
			bool loadFont(std::string name);
			sf::Font* requestFont(std::string name);
		private:
		};

		class MissingFontException : public std::exception
		{
		public:
			MissingFontException();
			sf::Font* what();
		};
	}
#endif Font_HPP
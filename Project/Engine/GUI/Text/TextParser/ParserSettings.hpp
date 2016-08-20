#ifndef PARSERSETTINGS_HPP
#define	PARSERSETTINGS_HPP

#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Color.hpp>
#include "../../../../Vector.h"
namespace GUI
{
	namespace Parser
	{
		struct ParserSettings
		{
			sf::Font& font;
			sf::Color& color;
			sf::Color& currentColor;
			double& characterSpacing;
			unsigned int& charSize;
			Vector2 trimPosition;
			ParserSettings(sf::Font& font, double& characterSpacing, unsigned int& charSize, sf::Color& color, Vector2 trimPosition = Vector2(0,25));
			ParserSettings(const ParserSettings& copy);
			ParserSettings& operator=(ParserSettings&right);
		};
	}
}


#endif
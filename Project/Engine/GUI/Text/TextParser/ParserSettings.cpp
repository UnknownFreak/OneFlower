#include "ParserSettings.hpp"


namespace GUI
{
	namespace Parser
	{
		ParserSettings::ParserSettings(sf::Font& font, double& characterSpacing, unsigned int& charSize, sf::Color& color, Vector2 trimPosition) :
			font(font), characterSpacing(characterSpacing), charSize(charSize), trimPosition(trimPosition), color(color)
		{
		}
		ParserSettings& ParserSettings::operator=(ParserSettings& right)
		{
			font = right.font;
			characterSpacing = right.characterSpacing;
			charSize = right.charSize;
			trimPosition = right.trimPosition;
			color = right.color;
			return *this;
		}
		ParserSettings::ParserSettings(const ParserSettings& copy) : font(copy.font), characterSpacing(copy.characterSpacing),
			charSize(copy.charSize), trimPosition(copy.trimPosition), color(copy.color)
		{

		}
	}
}

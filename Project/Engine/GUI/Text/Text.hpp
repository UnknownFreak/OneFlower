#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML\Graphics\Glyph.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\System\String.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include "../../../Vector.h"
#include "TextParser\TextParser.hpp"

namespace ParseArg = GUI::Parser::ParseArgument;
namespace GUI
{
	class Text : public sf::Drawable
	{

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates renderstates) const;

		sf::RenderTexture m_texture;
		sf::Sprite m_textSprite;

		sf::Font& m_font;
		sf::String m_text;
		sf::Color m_color = sf::Color::Black;

		Parser::TextParser parser;

		unsigned int m_charsize = 30;
		double m_charSpacing = 0;
		Vector2 m_position = Vector2(2,2);

		std::vector<Parser::ParseArgument::BaseParseArgument*> m_parseArguments;
		void clearParseArguments();

	public:

		/*
		*Sets a new character size valie, default value is 30.
		*/
		void setCharacterSize(unsigned int newCharacterSize, bool reparseText = false);

		/*
		*Sets a new character spacing value, default value is 0.
		*Negative values will make the text less spaced.
		*Positive values will make the text more spaced.
		*/
		void setCharacterSpacing(double newCharacterSpacing, bool reparseText = false);

		/*
		*Sets a new text string to be rendered.
		*/
		void setText(sf::String text, std::vector<Parser::ParseArgument::BaseParseArgument*> arguments);
		/*
		*Sets the position of the text.
		*/
		void setPosition(Vector2 pos);
		/*
		*Crops the text to desired size-
		*Where pos is the bounding location start (in pixels)
		*and size is the bounding location end (in pixels).
		*Pos should be default (0,0) unless the text should be cropped from above or the left side.
		*/
		void crop(Vector2i pos, Vector2i size);
		/*
		*Constructor to initialize the text.
		*@Param font, the font to use.
		*@param text, the initial value of the text.
		*/
		Text(sf::Font& font, sf::String text, std::vector<Parser::ParseArgument::BaseParseArgument*> arguments);
		/*
		Destructor to release the parse arguments on scope end.
		*/
		virtual ~Text();
	};
}
#endif
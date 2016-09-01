#include "FormatedText.hpp"
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

#if defined (_EDITOR_) || defined(_DEBUG)
#include <SFML\Graphics\VertexArray.hpp>
#endif

#include "TextParser\ParserSettings.hpp"

namespace GUI
{
	FormatedText::FormatedText(sf::Font& font, sf::String text,std::vector<Parser::ParseArgument::BaseParseArgument*> arguments ) : 
		m_font(font), m_text(text), parser(Parser::ParserSettings(m_font,m_charSpacing,m_charsize, m_color)), m_parseArguments(arguments)
	{
		m_textSprite.setTexture(parser.parse(text,m_parseArguments), true);
	}
	FormatedText::~FormatedText()
	{
		clearParseArguments();
	}
	void FormatedText::setText(sf::String text, std::vector<Parser::ParseArgument::BaseParseArgument*> arguments)
	{
		if (m_text != text)
		{
			m_text = text;
			clearParseArguments();
			m_parseArguments = arguments;
			m_textSprite.setTexture(parser.parse(m_text, m_parseArguments), true);
		}
	}
	void FormatedText::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
#if defined (_EDITOR_) || defined(_DEBUG)
		sf::VertexArray outline(sf::LinesStrip, 5);
		outline[0].color = sf::Color::Black;
		outline[1].color = sf::Color::Black;
		outline[2].color = sf::Color::Black;
		outline[3].color = sf::Color::Black;
		outline[4].color = sf::Color::Black;
		outline[0].position = sf::Vector2f(m_position.x, m_position.y);
		outline[1].position = sf::Vector2f(m_position.x + m_textSprite.getTextureRect().width, m_position.y);
		outline[2].position = sf::Vector2f(m_position.x + m_textSprite.getTextureRect().width, m_position.y + m_textSprite.getTextureRect().height);
		outline[3].position = sf::Vector2f(m_position.x, m_position.y + m_textSprite.getTextureRect().height);
		outline[4].position = sf::Vector2f(m_position.x, m_position.y);
		target.draw(outline, states);
#endif
		target.draw(m_textSprite,states);
	}

	void FormatedText::setPosition(Vector2 position)
	{
		m_position = position;
		m_textSprite.setPosition(m_position.x,m_position.y);
	}

	void FormatedText::crop(Vector2i pos, Vector2i size)
	{
		m_textSprite.setTextureRect(sf::IntRect(pos.x,pos.y, size.x,size.y));
	}
	void FormatedText::clearParseArguments()
	{
		for each (Parser::ParseArgument::BaseParseArgument* var in m_parseArguments)
			delete var;
	}
	void FormatedText::setCharacterSize(unsigned int characterSize, bool reparseText)
	{
		m_charsize = characterSize;
		if (reparseText)
			m_textSprite.setTexture(parser.parse(m_text, m_parseArguments), true);
	}
	void FormatedText::setCharacterSpacing(double characterSpacing, bool reparseText)
	{
		m_charSpacing = characterSpacing;
		if (reparseText)
			m_textSprite.setTexture(parser.parse(m_text, m_parseArguments), true);
	}
}
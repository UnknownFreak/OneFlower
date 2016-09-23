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
		m_state = ParseState::PreParse;
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
			m_state = ParseState::PreParse;
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

		switch (m_state)
		{
		case GUI::FormatedText::ParseState::PreParse:
			((FormatedText*)this)->parser.setup();
			((FormatedText*)this)->parseSize();
			target.draw(m_textSprite, states);
			((FormatedText*)this)->m_state = ParseState::Parse;
			break;
		case GUI::FormatedText::ParseState::Parse:
			((FormatedText*)this)->parseTexture();
			((FormatedText*)this)->m_textSprite.setTexture(((FormatedText*)this)->parser.getTexture());
			((FormatedText*)this)->m_state = ParseState::Done;
			//fall trough and draw the newly parsed text
		case GUI::FormatedText::ParseState::Done:
			target.draw(m_textSprite,states);
			break;
		default:
			break;
		}

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
	void FormatedText::parseSize()
	{
		parser.calculateTextureSize(m_text, m_parseArguments);
		
	}
	void FormatedText::parseTexture()
	{
		parser.createTexture(m_text, m_parseArguments);
	}
	void FormatedText::setCharacterSize(unsigned int characterSize, bool reparseText)
	{
		m_charsize = characterSize;
		if (reparseText)
			m_state = ParseState::PreParse;
	}
	void FormatedText::setCharacterSpacing(double characterSpacing, bool reparseText)
	{
		m_charSpacing = characterSpacing;
		if (reparseText)
			m_state = ParseState::PreParse;
	}
}
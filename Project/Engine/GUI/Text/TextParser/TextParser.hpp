#ifndef TEXTPARSER_HPP
#define TEXTPARSER_HPP

#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\System\String.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include "Comparer\BaseParseArgument.hpp"
#include "ParserSettings.hpp"
namespace GUI
{
	namespace Parser
	{
		class TextParser
		{

			Vector2i texSize;
			sf::Sprite sprite;
			sf::Glyph glyph;

			double advance;
			double kerning;
			double newLine;
			double lineSpacing;

			
			sf::RenderTexture m_parsedTextTexture;

			ParserSettings settings;

			void calculateTextureSize(sf::String& text, std::vector<Parser::ParseArgument::BaseParseArgument*>& args);
			void createTexture(sf::String& text, std::vector<Parser::ParseArgument::BaseParseArgument*>& args);


			void NewLine();

			bool parseArgument = false;

			int listIndex = -1;

			std::string doCompareArgument(Parser::ParseArgument::BaseParseArgument* argument);

			// does this need to return anything?
			void doReferenceArgument(Parser::ParseArgument::BaseParseArgument* argument);

		public:
			TextParser(ParserSettings settings);
			/*
			*Parses the string and returns a texture containing the parsed text to be drawn.
			*va_list of parse arguments.
			*use {0}, etc. to tell where in the string the parse argument is supposed to be.
			*/
			const sf::Texture& parse(sf::String& text, std::vector<Parser::ParseArgument::BaseParseArgument*>& args);
			void setParserSettings(ParserSettings settings);
		};
	}
}

#endif
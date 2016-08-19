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


			/*
			T has to be of type BaseParseArgument
			Valid types are
			IntCompareResult,
			DoubleCompareResult,
			FloatCompareResult,
			UintCompareResult,
			tY has to be of type depending on the type of T,
			IntCompare need to have int as tY,
			DoubleCompare need to have double as tY, etc.
			*param* the argument to cast to T
			*return* the formatted string from the argument passed*/
			template<class T, typename tY>
			std::string doCompareResult(Parser::ParseArgument::BaseParseArgument* argument)
			{
				std::string text;
				T* tType = (T*)argument;
				text = std::to_string(tType->first);
				typename Parser::ParseArgument::CompareResult<tY> tResult = tType->getCompared();
				if (tResult.result == tResult.Bad)
				{
					text.append(" -");
					text += std::to_string(tResult.value);
				}
				else if (tResult.result == tResult.Good)
				{
					text.append(" +");
					text += std::to_string(tResult.value);
				}
				return text;
			}

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
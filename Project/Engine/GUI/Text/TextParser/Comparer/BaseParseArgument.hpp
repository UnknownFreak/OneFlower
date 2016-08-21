#ifndef	BASEPARSEARGUMENT_HPP
#define BASEPARSEARGUMENT_HPP

#include <SFML\Graphics\Color.hpp>
namespace GUI
{
	namespace Parser
	{
		namespace ParseArgument
		{
			class BaseParseArgument
			{
			public:
				enum ArgumentType
				{
					Color,
					Compare,
					Reference,
					BeginList,
					NewListLine,
					EndList,
					Icon,
					None
				};
			protected:
				BaseParseArgument(ArgumentType type);
			public:
				ArgumentType type = None;
				virtual ~BaseParseArgument() = default;

				static BaseParseArgument* startList();
				static BaseParseArgument* newListLine();
				static BaseParseArgument* endList();
				static BaseParseArgument* colorArgument(sf::Color color);
				static BaseParseArgument* colorArgument(short r, short g, short b, short a);
				static BaseParseArgument* IntCompareArgument(int& first, int& second);
				static BaseParseArgument* IntReferenceArgument(int& reference);
			};
			
		}
	}
}

#endif
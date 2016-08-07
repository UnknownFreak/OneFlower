#include "BaseParseArgument.hpp"
#include "CompareResultTypes.hpp"
namespace GUI
{
	namespace Parser
	{
		namespace ParseArgument
		{
			BaseParseArgument::BaseParseArgument(ArgumentType type):type(type)
			{
			}
			BaseParseArgument* BaseParseArgument::startList()
			{
				return new BaseParseArgument(ArgumentType::BeginList);
			}
			BaseParseArgument* BaseParseArgument::newListLine()
			{
				return new BaseParseArgument(ArgumentType::NewListLine);
			}
			BaseParseArgument* BaseParseArgument::endList()
			{
				return new BaseParseArgument(ArgumentType::EndList);
			}
			BaseParseArgument* BaseParseArgument::colorArgument(sf::Color color)
			{
				return new BaseParseArgument(ArgumentType::Color);
			}
			BaseParseArgument* BaseParseArgument::colorArgument(short r, short g, short b, short a)
			{
				return new BaseParseArgument(ArgumentType::Color);
			}
			BaseParseArgument* BaseParseArgument::IntCompareArgument(int & first, int & second)
			{
				return new IntCompareResult(first, second);
			}
		}
	}
}
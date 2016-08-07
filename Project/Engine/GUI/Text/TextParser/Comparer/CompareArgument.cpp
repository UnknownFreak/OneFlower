#include "CompareArgument.hpp"

GUI::Parser::ParseArgument::BaseCompareArgument::BaseCompareArgument() :BaseParseArgument(ArgumentType::Compare)
{
}

GUI::Parser::ParseArgument::BaseCompareArgument::BaseCompareArgument(const BaseCompareArgument& copy) : BaseParseArgument(copy.type), comparingType(copy.comparingType)
{
}

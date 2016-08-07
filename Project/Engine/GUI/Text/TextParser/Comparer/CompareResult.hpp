#ifndef	COMPARERESULT_HPP
#define COMPARERESULT_HPP
#include "CompareArgument.hpp"
namespace GUI
{
	namespace Parser
	{
		namespace ParseArgument
		{
			template<class T>
			struct CompareResult
			{
				enum CompareResultColor
				{
					Good,
					Bad,
					Neutral,
				};
				T value;
				CompareResultColor result = Neutral;
				CompareResult(T _value, CompareResultColor _result) : value(_value), result(_result)
				{
				}
			};
		}
	}
}

#endif
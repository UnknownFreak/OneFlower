#ifndef COMPAREARGUMENT_HPP 
#define	COMPAREARGUMENT_HPP
#include "BaseParseArgument.hpp"
#include "CompareResult.hpp"

namespace GUI
{
	namespace Parser
	{
		namespace ParseArgument
		{
			
			class BaseCompareArgument : public BaseParseArgument
			{

			public:
				enum CompareType
				{
					Int,
					Float,
					Double,
					UInt,
					String,
				};

				CompareType comparingType;
				BaseCompareArgument();
				BaseCompareArgument(const BaseCompareArgument& copy);
				virtual ~BaseCompareArgument() = default;

				template<class T>
				CompareResult<T> compare(T& first, T& second)
				{
					if (first < second)
						return CompareResult<T>((second - first), CompareResult<T>::CompareResultColor::Good);
					else if (second < first)
						return CompareResult<T>((first - second), CompareResult<T>::CompareResultColor::Bad);
					return CompareResult<T>(first, CompareResult<T>::CompareResultColor::Neutral);
				}
			};
		}
	}
}


#endif
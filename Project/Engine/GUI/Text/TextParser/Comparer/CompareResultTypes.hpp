#ifndef COMPARERESULTTYPES_HPP
#define COMPARERESULTTYPES_HPP

#include "CompareArgument.hpp"


namespace GUI
{
	namespace Parser
	{
		namespace ParseArgument
		{
			template<class T>
			class ICompareResult : public BaseCompareArgument
			{
			public:
				
				T& first;
				T& second;
				
				ICompareResult(T& first, T& second) : BaseCompareArgument(), first(first),second(second)
				{
				}
				ICompareResult(const ICompareResult& copy) : BaseCompareArgument(copy), first(copy.first), second(copy.second)
				{
				}
				virtual ~ICompareResult<T>() = default;
				ICompareResult& operator=(const ICompareResult& right)
				{
					first = right.first;
					second = right.second;
					type = right.type;
					comparingType = right.comparingType;
					return *this;
				}
				CompareResult<T> getCompared()
				{
					return compare<T>(first,second);
				}
			};

			class IntCompareResult : public ICompareResult<int>
			{
			public:
				IntCompareResult(int& first, int& second) : ICompareResult(first, second)
				{
					comparingType = CompareType::Int;
				}
				IntCompareResult(const IntCompareResult& copy) : ICompareResult(copy)
				{
					comparingType = CompareType::Int;
				}
				IntCompareResult& operator= (const IntCompareResult& right)
				{
					first = right.first;
					second = right.second;
					type = right.type;
					comparingType = right.comparingType;
					return *this;
				}
			};

			class DoubleCompareResult : public ICompareResult<double>
			{
			public:
				DoubleCompareResult(double& first, double& second) : ICompareResult(first, second)
				{
					comparingType = CompareType::Double;
				}
				DoubleCompareResult(const DoubleCompareResult& copy) : ICompareResult(copy)
				{
					comparingType = CompareType::Double;
				}
				DoubleCompareResult& operator= (const DoubleCompareResult& right)
				{
					first = right.first;
					second = right.second;
					type = right.type;
					comparingType = right.comparingType;
					return *this;
				}
			};
		}
	}
}


#endif
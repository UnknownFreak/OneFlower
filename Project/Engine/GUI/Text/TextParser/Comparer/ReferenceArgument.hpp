#ifndef REFERENCEARGUMENT_HPP
#define REFERENCEARGUMENT_HPP
#include "BaseParseArgument.hpp"
namespace GUI
{
	namespace Parser
	{
		namespace ParseArgument
		{


			class BaseReferenceArgument : public BaseParseArgument
			{
			public:
				enum ReferenceType
				{
					Int,
					Double,
					Float,
					UInt,
					String
				};
				ReferenceType refType;
				
				BaseReferenceArgument() : BaseParseArgument(ParseArgument::BaseParseArgument::Reference)
				{
				}
				BaseReferenceArgument(BaseReferenceArgument& copy) : refType(copy.refType), BaseParseArgument(copy)
				{
				}
				BaseReferenceArgument& operator=(BaseReferenceArgument& right)
				{
					refType = right.refType;
					type = right.type;
					return *this;
				}
			};
		}
	}
}

#endif
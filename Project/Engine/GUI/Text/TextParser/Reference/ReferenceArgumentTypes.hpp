#ifndef REFERENCEARGUMENTTYPES_HPP
#define REFERENCEARGUMENTTYPES_HPP
#include "ReferenceArgument.hpp"
namespace GUI
{
	namespace Parser
	{
		namespace ParseArgument
		{

			class IntReference : public BaseReferenceArgument
			{
			public:
				int& myReference;
				IntReference(int& reference);
				IntReference(IntReference & copy);
				IntReference& operator=(IntReference& right);
			};
		}
	}
}

#endif
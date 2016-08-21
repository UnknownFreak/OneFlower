#include "ReferenceArgumentTypes.hpp"
namespace GUI
{
	namespace Parser
	{
		namespace ParseArgument
		{
			IntReference::IntReference(int& reference) : BaseReferenceArgument(), myReference(reference)
			{
				refType = ReferenceType::Int;
			}
			IntReference::IntReference(IntReference & copy) : BaseReferenceArgument(copy), myReference(copy.myReference)
			{
			}
			IntReference& IntReference::operator=(IntReference & right)
			{
				myReference = right.myReference;
				refType = right.refType;
				type = right.type;
				return *this;
			}
		}
	}
}

#ifndef VARIABLEINSTANCENAMEANDIDMAP_H
#define VARIABLEINSTANCENAMEANDIDMAP_H

#include <vector>
#include <map>
#include <Helpers/String.hpp>
namespace SpriterEngine
{
	class UniversalObjectInterface;
	class Variable;

	typedef std::vector<UniversalObjectInterface*> VariableInstanceVector;
	typedef std::map<Core::String, UniversalObjectInterface*> VariableInstanceNameMap;

	class VariableInstanceNameAndIdMap
	{
	public:
		VariableInstanceNameAndIdMap();
		~VariableInstanceNameAndIdMap();

		UniversalObjectInterface *getVariable(size_t variableIndex);
		UniversalObjectInterface *getVariable(Core::String variableName);

		void pushBackVariable(Variable * variable);

		bool isEmpty();

	private:
		VariableInstanceVector variables;
		VariableInstanceNameMap variableNameMap;
	};
}

#endif // VARIABLEINSTANCENAMEANDIDMAP_H

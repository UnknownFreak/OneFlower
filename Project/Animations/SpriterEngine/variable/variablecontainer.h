#ifndef VARIABLECONTAINER_H
#define VARIABLECONTAINER_H

#include <vector>

#include "../global/global.h"

#include "variable.h"

namespace SpriterEngine
{
	class VariableInstanceNameAndIdMap;

	typedef std::vector<Variable*> VariableVector;

	class VariableContainer
	{
	public:
		VariableContainer();
		virtual ~VariableContainer();

		Variable *getVariable(size_t variableIndex);

		void addStringVariable(Core::String variableName, Core::String defaultValue);
		void addIntVariable(Core::String variableName, s_int defaultValue);
		void addRealVariable(Core::String variableName, real defaultValue);

		void setupVariableInstances(VariableInstanceNameAndIdMap *variableMap);

		void setupDefaultVariableTimelines(Animation * animation, s_int objectId);

	private:
		VariableVector variables;
	};
}

#endif // ENTITY_H
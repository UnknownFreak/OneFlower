#ifndef BaseEngineModule_HPP
#define BaseEngineModule_HPP

#include <Helpers/Enum/EngineResourceTypes.hpp>

namespace EngineModule
{
	class ModuleManager;

	class BaseEngineModule
	{
		friend class ModuleManager;

	protected:

		virtual Enums::EngineResourceType& getType() const = 0;

	public:
		virtual ~BaseEngineModule() = 0
		{
		};
	};
}


#endif
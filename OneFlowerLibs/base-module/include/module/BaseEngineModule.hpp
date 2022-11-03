#ifndef BaseEngineModule_HPP
#define BaseEngineModule_HPP

#include <module/EngineResourceTypes.hpp>

namespace OneFlower::Module
{
	class ModuleManager;

	class BaseEngineModule
	{
		friend class ModuleManager;

	protected:
		bool disabled = false;

		virtual EngineResourceType& getType() const = 0;

	public:
		virtual ~BaseEngineModule() = 0
		{
		};

		void disable() { disabled = true; }
	};
}


#endif
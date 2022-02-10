#ifndef IEngineResource_HPP
#define	IEngineResource_HPP

#include <Module/BaseEngineModule.hpp>

// Enum included indirectly via BaseEngineModule

namespace Interfaces
{
	template <typename T>
	struct IEngineResource : public EngineModule::BaseEngineModule
	{
	
		static Enums::EngineResourceType type;
		static const Enums::EngineResourceType& getType()
		{ 
			return type;
		}
	};
}

#endif
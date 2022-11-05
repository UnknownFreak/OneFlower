#ifndef IEngineResource_HPP
#define	IEngineResource_HPP

#include <module/BaseEngineModule.hpp>

namespace OneFlower::Module::Interface
{
	template <typename T>
	struct IEngineResource : public Module::BaseEngineModule
	{
		static EngineResourceType type;
		static const EngineResourceType& getType()
		{ 
			return type;
		}
	};
}

#endif
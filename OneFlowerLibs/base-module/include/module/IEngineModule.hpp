#ifndef IEngineResource_HPP
#define	IEngineResource_HPP

#include <module/BaseEngineModule.hpp>

namespace of::module::Interface
{
	template <typename T>
	struct IEngineResource : public module::BaseEngineModule
	{
		static EngineResourceType type;
		static const EngineResourceType& getType()
		{ 
			return type;
		}
	};
}

#endif
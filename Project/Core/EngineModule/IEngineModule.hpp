#ifndef IEngineResource_HPP
#define	IEngineResource_HPP

#include "BaseEngineModule.hpp"


template <typename T>
struct IEngineResource : public BaseEngineModule
{
	
	static ResourceType type;
	static const ResourceType& getType()
	{
		return type;
	}
};

#endif
#ifndef IEngineResource_HPP
#define	IEngineResource_HPP

#include "BaseEngineResource.hpp"


template <typename>
struct IEngineResource : public BaseEngineResource
{
	
	static ResourceType type;
	static const ResourceType& getType()
	{
		return type;
	}

};

#endif
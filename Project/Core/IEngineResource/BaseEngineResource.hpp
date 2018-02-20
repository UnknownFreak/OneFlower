#ifndef BaseEngineResource_HPP
#define BaseEngineResource_HPP


enum class ResourceType
{
	Input,
	Time,
	Settings,
	Graphics,
	Physics,
	Event,
	WorldManager,
	WorldManagerAddon,
	SpriterContainer,
	AssetManager,
	Logger,
	StringConverter,
	Globals
};

class EngineResourceManager;

class BaseEngineResource
{
	friend class EngineResourceManager;

protected:

	virtual const ResourceType& getType() = 0;

public:
	virtual ~BaseEngineResource() = 0
	{
	};

};



#endif
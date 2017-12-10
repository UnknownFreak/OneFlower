#ifndef BaseEngineResource_HPP
#define BaseEngineResource_HPP


enum class ResourceType
{
	AssetManager,
	Graphics,
	StringConverter,
	Logger,
	Physics,
	Event,
	WorldManager,
	WorldManagerAddon,
	Time,
	Settings,
	Input,
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
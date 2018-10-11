#ifndef BaseEngineModule_HPP
#define BaseEngineModule_HPP


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
	Globals,
	GameVariableMapping,
	NOT_SET,
};

class EngineModuleManager;

class BaseEngineModule
{
	friend class EngineModuleManager;

protected:

	virtual const ResourceType& getType() = 0;

public:
	virtual ~BaseEngineModule() = 0
	{
	};

};



#endif
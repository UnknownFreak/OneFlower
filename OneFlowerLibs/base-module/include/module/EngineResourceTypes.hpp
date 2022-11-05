#ifndef EngineResourceTypes_HPP
#define EngineResourceTypes_HPP

namespace OneFlower::Module
{
	enum class EngineResourceType
	{
		Input,
		Time,
		Settings,
		Graphics,
		Physics,
		WorldManager,
		WorldManagerAddon,
		SpriterContainer,
		AssetManager,
		Logger,
		StringConverter,
		Globals,
		GameVariableMapping,
		ModLoader,
		TextureLoader,
		Console,
		UIHandler,
		ObjectInstanceHandler,
		RandomGen,
		SaveFile,
		MeshLoader,
		ShaderLoader,
		EngineSettings,
		WindowProxy,
		NOT_SET,
	};
}

#endif 
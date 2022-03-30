#include "TileAtlas.hpp"

#include <Module/EngineModuleManager.hpp>
#include <Module/Logger/OneLogger.hpp>

Core::uuid Interfaces::Trait<File::Resource::Texture::TileAtlas>::typeId = Core::uuid("85e407fd-f61e-4d81-8928-6b206d42b0cc");

namespace File::Resource::Texture
{

	TileAtlas::TileAtlas()
	{
	}

	TileAtlas::TileAtlas(const TileAtlas& copy) : atlas(copy.atlas), Interfaces::IRequestable(copy), Interfaces::IObject(copy)
	{
	}

	TileAtlas& TileAtlas::operator=(const TileAtlas& right)
	{
		Interfaces::IRequestable::operator=(right);
		Interfaces::IObject::operator=(right);

		atlas = right.atlas;
		return *this;
	}

	void TileAtlas::addAtlasPos(const Core::String& tileType, const float& x, const float& y)
	{
		atlas.insert({ tileType, {x, y} });
	}

	void TileAtlas::addAtlasPos(const Core::String& tileType, const Core::Vector2f& vec)
	{
		atlas.insert({ tileType, vec });
	}

	void TileAtlas::removeAtlasPos(const Core::String& tileType)
	{
		if (atlas.find(tileType) != atlas.end())
			atlas.erase(tileType);
	}

	Core::Vector2f& TileAtlas::get(const Core::String& tileType)
	{
		if (atlas.find(tileType) != atlas.end())
			return atlas[tileType];
		auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::Resource::Texture::TileAtlas");
		logger.Error("Unable to load tileType [" + tileType + "] for atlas [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
		return def;
	}

	Interfaces::TypeInfo TileAtlas::getTrait() const
	{
		return { Interfaces::Trait<TileAtlas>::typeId };
	}
}

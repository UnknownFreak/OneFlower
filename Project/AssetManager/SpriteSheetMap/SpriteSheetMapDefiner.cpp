#include "SpriteSheetMapRef.hpp"
#include "../AssetManagerCore.hpp"
#include "../TextureLoader.hpp"


const SpriteSheetMap * SpriteSheetMapRef::getSpriteSheetMap()
{
#ifdef _EDITOR_
	return &mySpriteSheetMap;
#else
	return &mySpriteSheetMap.get();
#endif
}

bool SpriteSheetMapRef::isReady()
{
#ifdef _EDITOR_
	return true;
#else
	return mySpriteSheetMap.valid();
#endif
}
#ifdef _EDITOR_
void SpriteSheetMapRef::setNewFuture(SpriteSheetMap map)
#else
void SpriteSheetMapRef::setNewFuture(std::shared_future<SpriteSheetMap> map)
#endif
{
	mySpriteSheetMap = map;
}

void SpriteSheetMapRef::reloadMap()
{
	// load from database <>
	//mySpriteSheetMap = Engine::Textureloader.loadTextureAsync(name);
}


SpriteSheetMapRef::SpriteSheetMapRef(Core::String name) : name(name)
{
	reloadMap();
}

SpriteSheetMapRef::SpriteSheetMapRef(const SpriteSheetMapRef & copy) : name(copy.name), mySpriteSheetMap(copy.mySpriteSheetMap), useCount(copy.useCount)
{
}

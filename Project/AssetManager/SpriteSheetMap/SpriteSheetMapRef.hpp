#ifndef SpriteSheetMapRef_HPP
#define SpriteSheetMapRef_HPP

#include "SpriteSheetMap.hpp"
#include <Core/String.hpp>
#ifndef _EDITOR_
#include<future>
#endif
class SpriteSheetMapRef
{
	friend class TextureLoader;
#ifdef _EDITOR_
	SpriteSheetMap mySpriteSheetMap;
#else
	std::shared_future<SpriteSheetMap> mySpriteSheetMap;
#endif
public:
	SpriteSheetMapRef(Core::String name);
	SpriteSheetMapRef(const SpriteSheetMapRef& copy);

	const SpriteSheetMap* getSpriteSheetMap();
	bool isReady();

	size_t useCount = 0;
	Core::String name;
#ifdef _EDITOR_
	void setNewFuture(SpriteSheetMap future);
#else
	void setNewFuture(std::shared_future<SpriteSheetMap> future);

#endif
	void reloadMap();
};

#endif
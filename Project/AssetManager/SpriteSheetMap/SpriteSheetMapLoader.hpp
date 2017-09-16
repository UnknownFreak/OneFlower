#ifndef SPRITESHEETMAPLOADER_HPP
#define SPRITESHEETMAPLOADER_HPP

#include "SpriteSheetMapRef.hpp"
#include "SpriteSheetMap.hpp"
#include <Core/String.hpp>
#include <map>
#ifndef _EDITOR_
#include <future>
#endif
//#include "../Settings/EngineSettings.hpp"

class TextureLoader
{
	/*std::map<Settings::EngineSettings::TextureRes,*/
	std::map<std::pair<Core::String, Core::String>, SpriteSheetMapRef>/*> */loadedSpriteSheetMap;
	bool loadSpriteSheetMap(const Core::String& name);
	SpriteSheetMap loadSpriteSheetMap_internal(const Core::String& name);

public:
	// used by TextureRef
#ifdef _EDITOR_
	SpriteSheetMap loadSpriteSheetMapAsync(const Core::String& name);
#else
	std::shared_future<SpriteSheetMap> loadSpriteSheetMapAsync(Core::String& name);
#endif
	SpriteSheetMapRef* requestSpriteSheetMap(const Core::String& name);

	//request removal of texture if its not in use
	void requestRemovalOfTexture(const Core::String& name);

};


#endif
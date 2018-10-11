#ifndef SpriterInstanceContainer_HPP
#define SpriterInstanceContainer_HPP

#include <map>

#include <Core\String.hpp>
#include <AssetManager\SpriteRef.hpp>

#include "SpriterEngine\spriterengine.h"

class SpriterInstanceContainer : public IEngineResource<SpriterInstanceContainer>
{
	std::map<std::pair<Core::String, std::pair<Core::String, size_t>>, SpriterEngine::SpriterModel*> modelFiles;
	// Below does not need to be deleted, as they get deleted when the SpriterModel is deleted.
	typedef std::pair<Core::String, std::pair<Core::String, size_t>> key;

	SpriteRef* ref = nullptr;

public:

	SpriterInstanceContainer();
	~SpriterInstanceContainer();

	SpriterEngine::EntityInstance* requestModel(Core::String _modelFile, Core::String _modelName, std::pair<Core::String, size_t> _textureMapId, SpriteRef*& sprite);

	// Inherited via IEngineResource
	virtual const ResourceType & getType() override;

};


#endif
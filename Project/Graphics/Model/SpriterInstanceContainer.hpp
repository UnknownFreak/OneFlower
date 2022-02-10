#ifndef SpriterInstanceContainer_HPP
#define SpriterInstanceContainer_HPP

#include <map>
#include <Interfaces/IEngineModule.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Helpers/uuid.hpp>
#include <Helpers\String.hpp>

#include <Graphics/Spriter/SpriterEngine/spriterengine.h>

class SpriterInstanceContainer : public Interfaces::IEngineResource<SpriterInstanceContainer>
{
	std::map<std::pair<Core::String, std::pair<Core::String, Core::uuid>>, SpriterEngine::SpriterModel*> modelFiles;
	// Below does not need to be deleted, as they get deleted when the SpriterModel is deleted.
	typedef std::pair<Core::String, std::pair<Core::String, Core::uuid>> key;

	std::shared_ptr<sf::Sprite> ref;

public:

	SpriterInstanceContainer();
	~SpriterInstanceContainer();

	SpriterEngine::EntityInstance* requestModel(Core::String _modelFile, Core::String _modelName, std::pair<Core::String, Core::uuid> _textureMapId, std::shared_ptr<sf::Sprite>& sprite);

	// Inherited via IEngineResource
	Enums::EngineResourceType& getType() const;

};


#endif
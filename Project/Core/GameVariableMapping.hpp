#ifndef GameVariableMapping_HPP
#define GameVariableMapping_HPP

#include <memory>

#include "IEngineResource\IEngineResource.hpp"
#include "String.hpp"

class GameVariableMapping : public IEngineResource<GameVariableMapping>
{

	std::pair<Core::String, size_t> animationVariableId;
	std::pair<Core::String, size_t> mainMenuId;
	std::pair<Core::String, size_t> startingZoneId;
	std::pair<Core::String, size_t> startingPointId;

public:

	// Inherited via IEngineResource
	virtual const ResourceType & getType() override;

};


#endif
#ifndef GameVariableMapping_HPP
#define GameVariableMapping_HPP

#include <memory>
#include <vector>

#include "IEngineResource\IEngineResource.hpp"
#include "String.hpp"

class GameVariableMapping : public IEngineResource<GameVariableMapping>
{

	std::vector<Core::String> empty;
	Core::String animationVariableId;
	std::pair<Core::String, size_t> mainMenuId;
	std::pair<Core::String, size_t> startingZoneId;
	std::pair<Core::String, size_t> startingPointId;

public:

	std::vector<Core::String>& getAnimationList();

#ifdef _EDITOR_
	Core::String getAnimationVariableName();
#endif

	// Inherited via IEngineResource
	virtual const ResourceType & getType() override;

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(animationVariableId);
	}

	template<class Archive>
	void load(Archive& ar)
	{
		ar(animationVariableId);
	}
};


#endif
#include "GameModeRequirement.hpp"
#include <module/SaveFile.hpp>

namespace Requirement
{
	bool GameModeRequirement::fullfilled()
	{
		return of::engine::GetModule<of::module::SaveFile>().getGameModeId() == gameModeId;
	}
	std::unique_ptr<Requirement> GameModeRequirement::clone() const
	{
		return std::make_unique<GameModeRequirement>(*this);
	}
}
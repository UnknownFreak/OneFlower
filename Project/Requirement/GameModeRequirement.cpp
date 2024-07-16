#include "GameModeRequirement.hpp"
#include <file/SaveFile.hpp>

namespace Requirement
{
	bool GameModeRequirement::fullfilled()
	{
		return of::engine::GetModule<of::file::SaveFile>().getGameModeId() == gameModeId;
	}
	std::unique_ptr<Requirement> GameModeRequirement::clone() const
	{
		return std::make_unique<GameModeRequirement>(*this);
	}
}
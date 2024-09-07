#include "GameModeRequirement.hpp"
#include <session/gameSession.hpp>

namespace Requirement
{
	bool GameModeRequirement::fullfilled()
	{
		return of::session::get().getGameModeId() == gameModeId;
	}
	std::unique_ptr<Requirement> GameModeRequirement::clone() const
	{
		return std::make_unique<GameModeRequirement>(*this);
	}
}
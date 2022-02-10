#include "GameModeRequirement.hpp"
#include <File/SaveFile.hpp>
namespace Requirement
{
	bool GameModeRequirement::fullfilled()
	{
		return Engine::GetModule<File::SaveFile>().getGameModeId() == gameModeId;
	}
	std::unique_ptr<Requirement> GameModeRequirement::clone() const
	{
		return std::make_unique<GameModeRequirement>(*this);
	}
}
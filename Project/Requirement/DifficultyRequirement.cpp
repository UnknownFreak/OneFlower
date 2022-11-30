#include "DifficultyRequirement.hpp"

#include <File/SaveFile.hpp>

namespace Requirement
{
	bool DifficultyRequirement::fullfilled()
	{
		auto& savefile = of::engine::GetModule<File::SaveFile>();
		return savefile.getCustomDiffId() == customDiff || savefile.getDifficulty() == level;
	}

	std::unique_ptr<Requirement> DifficultyRequirement::clone() const
	{
		return std::make_unique<DifficultyRequirement>(*this);
	}
}
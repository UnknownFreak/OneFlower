#include "DifficultyRequirement.hpp"

#include <file/SaveFile.hpp>

namespace Requirement
{
	bool DifficultyRequirement::fullfilled()
	{
		auto& savefile = of::session::get();
		return savefile.getCustomDiffId() == customDiff || savefile.getDifficulty() == level;
	}

	std::unique_ptr<Requirement> DifficultyRequirement::clone() const
	{
		return std::make_unique<DifficultyRequirement>(*this);
	}
}
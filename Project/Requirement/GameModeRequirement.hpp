#ifndef GameModeRequirement_HPP
#define GameModeRequirement_HPP

#include "Requirement.hpp"
#include <file/FileId.hpp>

namespace Requirement
{
	class GameModeRequirement : public Requirement
	{
	public:

		of::file::FileId gameModeId;

		// Inherited via Requirement
		virtual bool fullfilled() override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(gameModeId);
		}
		template <class Archive>
		void load(Archive& ar)
		{
			ar(gameModeId);
		}


		// Inherited via Requirement
		virtual std::unique_ptr<Requirement> clone() const override;

	};
}

#endif
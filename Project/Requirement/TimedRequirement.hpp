#ifndef TimedRequirement_HPP
#define TimedRequirement_HPP

#include <file/FileId.hpp>
#include <Helpers/TickTimer.hpp>
#include "Requirement.hpp"

namespace Requirement
{
	class TimedRequirement : public Requirement
	{
		void loadTimerFromSave();
	public:

		~TimedRequirement();
		bool fullfilledIftimeRanOut;
		of::file::FileId timerId;
		Core::TickTimerInfo timerInfo;
		// Inherited via Requirement
		virtual bool fullfilled() override;

		virtual void start() override;
		virtual void reset() override;
		virtual void stop() override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(fullfilledIftimeRanOut);
			ar(timerId);
			ar(timerInfo);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(fullfilledIftimeRanOut);
			ar(timerId);
			ar(timerInfo);
			loadTimerFromSave();
		}

		// Inherited via Requirement
		virtual std::unique_ptr<Requirement> clone() const override;
	};
}

#endif
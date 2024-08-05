#ifndef TimedRequirement_HPP
#define TimedRequirement_HPP

#include <file/FileId.hpp>
#include <timer/tickTimer.hpp>

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
		of::timer::TickTimer timer;
		// Inherited via Requirement
		virtual bool fullfilled() override;

		virtual void start() override;
		virtual void reset() override;
		virtual void stop() override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(fullfilledIftimeRanOut);
			ar(timer);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(fullfilledIftimeRanOut);
			ar(timer);
			loadTimerFromSave();
		}

		// Inherited via Requirement
		virtual std::unique_ptr<Requirement> clone() const override;
	};
}

#endif
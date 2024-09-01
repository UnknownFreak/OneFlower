#include "TimedRequirement.hpp"

#include <file/SaveFile.hpp>


namespace Requirement
{

	void TimedRequirement::loadTimerFromSave()
	{
		auto& saveFile = of::session::get();
		saveFile;
		// TODO replace with TimerSaveState
		//if (saveFile.isTimerSaved(timerId))
		//{
		//	timerInfo = saveFile.getTickTimer(timerId);
		//}
		//TODO: Move to questing module and initalize once the save file have been loaded.
		//if (timerInfo.started && !timerInfo.finished)
		//	start();
	}

	TimedRequirement::~TimedRequirement()
	{
	}

	bool TimedRequirement::fullfilled()
	{
		if (timer.started || timer.finished)
		{
			auto fraction = timer.getFraction();
			return fullfilledIftimeRanOut ? fraction > 1.f : fraction < 1.f;
		}
		else
			// timer never started so it have to be fullfilled depending on context of timer.
			// e.g survive for x seconds, or defeat enemies in x time
			return fullfilledIftimeRanOut ? false : true;
	}

	void TimedRequirement::start()
	{
		timer.start();
	}

	void TimedRequirement::reset()
	{
		timer.reset();
	}

	void TimedRequirement::stop()
	{
		timer.stop();
	}

	std::unique_ptr<Requirement> TimedRequirement::clone() const
	{
		return std::make_unique<TimedRequirement>(*this);
	}
}

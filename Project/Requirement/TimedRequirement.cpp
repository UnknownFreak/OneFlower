#include "TimedRequirement.hpp"

#include <File/SaveFile.hpp>
#include <Module/OneTime.hpp>


namespace Requirement
{

	void TimedRequirement::loadTimerFromSave()
	{
		auto& saveFile = Engine::GetModule<File::SaveFile>();
		if (saveFile.isTimerSaved(timerId))
		{
			timerInfo = saveFile.getTickTimer(timerId);
		}
		//TODO: Move to questing module and initalize once the save file have been loaded.
		//if (timerInfo.started && !timerInfo.finished)
		//	start();
	}

	TimedRequirement::~TimedRequirement()
	{
		if (timerInfo.started && !timerInfo.finished)
			stop();
	}

	bool TimedRequirement::fullfilled()
	{
		if (timerInfo.started || timerInfo.finished)
		{
			auto& timer = Engine::GetModule<EngineModule::Time>();
			if (timer.exists(timerId))
			{
				auto& tickTimer = timer.getTickTimer(timerId);
				timerInfo = tickTimer.getInfo();
				Engine::GetModule<File::SaveFile>().setTickTimer(timerId, timerInfo);
				if (timerInfo.finished)
					stop();
			
				auto fraction = tickTimer.getFraction();
				return fullfilledIftimeRanOut ? fraction > 1.f : fraction < 1.f;
			}
			auto fraction = timerInfo.currentTime / timerInfo.maxTime;
			return fullfilledIftimeRanOut ? fraction > 1.f : fraction < 1.f;
		}
		else
			// timer never started so it have to be fullfilled depending on context of timer.
			// e.g survive for x seconds, or defeat enemies in x time
			return fullfilledIftimeRanOut ? false : true;
	}

	void TimedRequirement::start()
	{
		if (!timerInfo.finished)
		Engine::GetModule<EngineModule::Time>().addTicKTimer(timerId, Core::TickTimer::from(timerInfo));
		timerInfo.started = true;
	}

	void TimedRequirement::reset()
	{
		timerInfo.started = false;
		timerInfo.currentTime = 0.f;
		timerInfo.finished = false;
		Engine::GetModule<File::SaveFile>().setTickTimer(timerId, timerInfo);
	}

	void TimedRequirement::stop()
	{
		timerInfo.started = false;
		Engine::GetModule<EngineModule::Time>().removeTimer(timerId);
	}

	std::unique_ptr<Requirement> TimedRequirement::clone() const
	{
		return std::make_unique<TimedRequirement>(*this);
	}
}

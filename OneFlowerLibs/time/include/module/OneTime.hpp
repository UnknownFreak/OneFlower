#ifndef OneTime_HPP
#define OneTime_HPP

#include <unordered_map>
#include <mutex>

#include <file/FileId.hpp>

#include <utils/HighResolutionClock.hpp>
#include <utils/common/String.hpp>

#include <resource/TickTimer.hpp>

#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>

namespace of::module
{

	class Time : public of::module::interface::IEngineResource<Time>
	{
		std::mutex mtx;
	public:

		Time();

		float deltaTime() const;

		::utils::HighResolutionClock& getTimer(const of::common::String&);
		bool time(const of::common::String&, const double& msec);
		void remove(const of::common::String& name);

		void addTicKTimer(const of::file::FileId& timerId, const resource::TickTimer& timer);
		bool exists(const of::file::FileId& timerId) const;
		resource::TickTimer& getTickTimer(const of::file::FileId& timerId);
		void removeTimer(const of::file::FileId& timerId);

		const float update_ms = 1.f / 60.f;

		float elapsed;
		::utils::HighResolutionClock clock;

		float physicsElapsed;
		::utils::HighResolutionClock physicsClock;

		of::module::EngineResourceType& getType() const
		{
			return type;
		}

	private:
		::utils::HighResolutionClock timer;

		std::unordered_map<of::common::String, ::utils::HighResolutionClock> timers;
		std::unordered_map<of::file::FileId, resource::TickTimer> tickTimers;

	public:
		virtual void Simulate(const float& fElapsedTime);

	};
}

#endif
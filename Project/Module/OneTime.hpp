#ifndef OneTime_HPP
#define OneTime_HPP

#include <unordered_map>
#include <mutex>

#include <utils/HighResolutionClock.hpp>
#include <File/Mod/ModFileUUIDHelper.hpp>

#include <utils/common/String.hpp>
#include <Helpers/TickTimer.hpp>
#include <module/IEngineModule.hpp>
#include <Interfaces/ISimulatable.hpp>

namespace EngineModule
{

	class Time : public of::module::interface::IEngineResource<Time>, Interfaces::ISimulatable
	{
		std::mutex mtx;
	public:

		Time();

		float deltaTime() const;

		utils::HighResolutionClock& getTimer(const of::common::String&);
		bool time(const of::common::String&, const double& msec);
		void remove(const of::common::String& name);

		void addTicKTimer(const File::Mod::ModFileUUIDHelper& timerId, const Core::TickTimer& timer);
		bool exists(const File::Mod::ModFileUUIDHelper& timerId) const;
		Core::TickTimer& getTickTimer(const File::Mod::ModFileUUIDHelper& timerId);
		void removeTimer(const File::Mod::ModFileUUIDHelper& timerId);

		const float update_ms = 1.f / 60.f;

		float elapsed;
		utils::HighResolutionClock clock;

		float physicsElapsed;
		utils::HighResolutionClock physicsClock;

		of::module::EngineResourceType& getType() const
		{
			return type;
		}

	private:
		utils::HighResolutionClock timer;

		//LOW: Put this in Definer to avoid include of Map:String?
		std::unordered_map<of::common::String, utils::HighResolutionClock> timers;
		std::unordered_map<File::Mod::ModFileUUIDHelper, Core::TickTimer> tickTimers;

	public:
		// Inherited via ISimulatable
		virtual void Simulate(const float& fElapsedTime) override;

	};
}

#endif
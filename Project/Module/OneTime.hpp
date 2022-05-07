#ifndef OneTime_HPP
#define OneTime_HPP

#include <unordered_map>
#include <mutex>

#include <utils/HighResolutionClock.hpp>
#include <File/Mod/ModFileUUIDHelper.hpp>

#include <Helpers/String.hpp>
#include <Helpers/TickTimer.hpp>
#include <Interfaces/IEngineModule.hpp>
#include <Interfaces/ISimulatable.hpp>

namespace EngineModule
{

	class Time : public Interfaces::IEngineResource<Time>, Interfaces::ISimulatable
	{
		std::mutex mtx;
	public:

		Time();

		float deltaTime() const;

		utils::HighResolutionClock& getTimer(const Core::String&);
		bool time(const Core::String&, const double& msec);
		void remove(const Core::String& name);

		void addTicKTimer(const File::Mod::ModFileUUIDHelper& timerId, const Core::TickTimer& timer);
		bool exists(const File::Mod::ModFileUUIDHelper& timerId) const;
		Core::TickTimer& getTickTimer(const File::Mod::ModFileUUIDHelper& timerId);
		void removeTimer(const File::Mod::ModFileUUIDHelper& timerId);

		const float update_ms = 1.f / 60.f;

		float elapsed;
		utils::HighResolutionClock clock;

		float physicsElapsed;
		utils::HighResolutionClock physicsClock;

		Enums::EngineResourceType& getType() const
		{
			return type;
		}

	private:
		utils::HighResolutionClock timer;

		//LOW: Put this in Definer to avoid include of Map:String?
		std::unordered_map<Core::String, utils::HighResolutionClock> timers;
		std::unordered_map<File::Mod::ModFileUUIDHelper, Core::TickTimer> tickTimers;

	public:
		// Inherited via ISimulatable
		virtual void Simulate(const float& fElapsedTime) override;

	};
}

#endif
#ifndef OneTime_HPP
#define OneTime_HPP

#include <unordered_map>
#include <mutex>

#include <SFML\System\Clock.hpp>
#include <File/ModFileUUIDHelper.hpp>

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

		double deltaTime();

		sf::Clock& getTimer(const Core::String&);
		bool time(const Core::String&, const double& msec);
		void remove(const Core::String& name);

		void addTicKTimer(const ModFileUUIDHelper& timerId, const Core::TickTimer& timer);
		bool exists(const ModFileUUIDHelper& timerId) const;
		Core::TickTimer& getTickTimer(const ModFileUUIDHelper& timerId);
		void removeTimer(const ModFileUUIDHelper& timerId);

		const sf::Time update_ms = sf::seconds(1.f / 60.f);

		sf::Time elapsed;
		sf::Clock clock;

		sf::Time physicsElapsed;
		sf::Clock physicsClock;

		Enums::EngineResourceType& getType() const
		{
			return type;
		}

	private:
		sf::Clock timer;

		//LOW: Put this in Definer to avoid include of Map:String?
		std::unordered_map<Core::String, sf::Clock> timers;
		std::unordered_map<ModFileUUIDHelper, Core::TickTimer> tickTimers;

	public:
		// Inherited via ISimulatable
		virtual void Simulate(const float& fElapsedTime) override;

	};
}

#endif
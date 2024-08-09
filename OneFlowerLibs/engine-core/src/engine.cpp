#include <engine/engine.hpp>

#include <engine/settings.hpp>
#include <rng/rng.hpp>
#include <timer/timer.hpp>

#include <logger/logger.hpp>

namespace of::engine
{

	void initialize()
	{
		settings::init();
		rng::init();

		auto& logger = of::logger::get().getLogger("Main");
		logger.Info("Initializing Modules group: Core");
		timer::init();

	}

	void shutdown()
	{
		timer::shutdown();

		rng::shutdown();
		settings::shutdown();

	}
}
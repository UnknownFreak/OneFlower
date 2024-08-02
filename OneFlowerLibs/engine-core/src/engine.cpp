#include <engine/engine.hpp>

#include <engine/settings.hpp>
#include <rng/rng.hpp>

#include <logger/Logger.hpp>

namespace of::engine
{

	void initialize()
	{
		settings::init();
		rng::init();
	}

	void shutdown()
	{
		rng::shutdown();
		settings::shutdown();
	}
}
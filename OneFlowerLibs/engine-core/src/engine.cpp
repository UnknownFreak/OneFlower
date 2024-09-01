#include <engine/engine.hpp>

#include <engine/settings.hpp>
#include <rng/rng.hpp>
#include <timer/timer.hpp>

#include <object/internalInstanceHandler.hpp>
#include <session/internalGameSession.hpp>

#include <logger/logger.hpp>

namespace of::engine
{

	/* Preferred init order:
	
	main()
	{
		external -> logger initialize

		initialize() <--- this method

		{
			engine settings
			rng generator 
			log -> Core
			timer
			archive ??

			log -> asset
			object
			session
			loaders texture, mesh, shader, depends on archive


			log -> engine
			scene
			input
			proxy?? do we need it?
			windowproxy?? do we need it

			log -> loading external modules
		}

		external -> courier
		external -> gameConfig

		runGame() -> physics, ui, editor ui

		shutdown() <--- method below this
		{

			reverse order of initialize
		}
	}
	*/

	void initialize()
	{
		settings::init();
		rng::init();

		auto& logger = of::logger::get().getLogger("Main");
		logger.Info("Initializing Modules group: Core");
		timer::init();

		
		logger.Info("Initializing Modules group: (internal) Asset Management");

		object::init();
		session::init();

	}

	void shutdown()
	{
		session::shutdown();
		object::shutdown();
		timer::shutdown();

		rng::shutdown();
		settings::shutdown();

	}
}
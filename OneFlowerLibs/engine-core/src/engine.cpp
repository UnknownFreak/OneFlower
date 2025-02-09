#include <engine/engine.hpp>

#include <engine/settings.hpp>
#include <rng/rng.hpp>
#include <timer/timer.hpp>

#include <asset/internalAsset.hpp>
#include <object/internalInstanceHandler.hpp>
#include <input/internalInput.hpp>
#include <session/internalGameSession.hpp>
#include <locale/internalLocale.hpp>

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
			archive => asset
			locale

			log -> asset
			object
			session


			log -> engine
			scene
			input
			proxy?? do we need it?
			windowproxy?? do we need it

			log -> loading external modules
		}

		external -> courier

		asset::loadOrder("loadOrder.order")

		graphics()
		{
			loaders for texture, mesh and shader (auto cleanup when graphics is finished)
		}

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
		asset::init();
		locale::init();
		input::init();

		logger.Info("Initializing Modules group: (internal) Asset Management");

		object::init();
		session::init();
	}

	void shutdown()
	{
		session::shutdown();
		object::shutdown();

		input::shutdown();
		locale::shutdown();
		asset::shutdown();
		timer::shutdown();

		rng::shutdown();
		settings::shutdown();

	}
}
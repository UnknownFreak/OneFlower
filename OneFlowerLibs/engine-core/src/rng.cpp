#include <rng/rng.hpp>
#include <module/settings/EngineSettings.hpp>
#include <logger/Logger.hpp>

of::rng::RandomGen* g_rng = nullptr;

namespace of::rng
{
	RandomGen::RandomGen() : rd(), engine(rd())
	{
		if (engine::GetModule<of::module::Settings>().useFixedSeed())
			engine.seed(0);
	}

	int RandomGen::randomInt()
	{
		return i(engine);
	}

	int RandomGen::randomInt(const int min, const int max)
	{
		return i(engine, std::uniform_int_distribution<int>::param_type(min, max));
	}

	float RandomGen::randomFloat()
	{
		return f(engine);
	}
	float RandomGen::randomFloat(const float min, const float max)
	{
		return f(engine, std::uniform_real_distribution<float>::param_type(min, max));
	}
	double RandomGen::randomDouble()
	{
		return d(engine);
	}

	double RandomGen::randomDouble(const double min, const double max)
	{
		return d(engine, std::uniform_real_distribution<double>::param_type(min, max));
	}

	void init()
	{
		if (g_rng == nullptr)
		{
			engine::GetModule<of::logger::Logger>().Info("Initializing module: Rng");
			g_rng = new RandomGen();
		}
		else
		{
			engine::GetModule<of::logger::Logger>().getLogger("of::rng").Warning("Trying to initialize random geneartor multiple times!");
		}
	}

	void shutdown()
	{
		delete g_rng;
		g_rng = nullptr;
	}

	RandomGen& get()
	{
		return *g_rng;
	}
}
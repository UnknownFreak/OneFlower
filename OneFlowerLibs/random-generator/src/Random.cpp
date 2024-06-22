#include <module/Random.hpp>
#include <module/settings/EngineSettings.hpp>

of::module::EngineResourceType  of::module::interface::IEngineResource< of::module::RandomGen>::type = of::module::EngineResourceType::RandomGen;

std::random_device  of::module::RandomGen::rd;
std::mt19937_64  of::module::RandomGen::engine(of::module::RandomGen::rd());

namespace of::module
{
	RandomGen::RandomGen()
	{
		if (engine::GetModule<Settings>().useFixedSeed())
			engine.seed(0);
		//else
		//engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	}
	int RandomGen::random_int()
	{
		return i(engine);
	}

	int RandomGen::random_int(const int& min, const int& max)
	{
		return i(engine, std::uniform_int_distribution<int>::param_type(min, max));
	}
	float RandomGen::random_float()
	{
		return f(engine);
	}
	float RandomGen::random_float(const float& min, const float& max)
	{
		return f(engine, std::uniform_real_distribution<float>::param_type(min, max));
	}
	double RandomGen::random_double()
	{
		return d(engine);
	}

	double RandomGen::random_double(const double& min, const double& max)
	{
		return d(engine, std::uniform_real_distribution<double>::param_type(min, max));
	}
	EngineResourceType& RandomGen::getType() const
	{
		return type;
	}
}
#include <module/Random.hpp>
#include <module/ModuleManager.hpp>
#include <module/settings/EngineSettings.hpp>

OneFlower::Module::EngineResourceType  OneFlower::Module::Interface::IEngineResource< OneFlower::Module::RandomGen>::type = OneFlower::Module::EngineResourceType::RandomGen;

std::random_device  OneFlower::Module::RandomGen::rd;
std::mt19937_64  OneFlower::Module::RandomGen::engine(OneFlower::Module::RandomGen::rd());

namespace OneFlower::Module
{
	RandomGen::RandomGen()
	{
		if (Engine::GetModule<Settings>().useFixedSeed())
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
		return i(engine, std::uniform_int<int>::param_type(min, max));
	}
	float RandomGen::random_float()
	{
		return f(engine);
	}
	float RandomGen::random_float(const float& min, const float& max)
	{
		return f(engine, std::uniform_real<float>::param_type(min, max));
	}
	double RandomGen::random_double()
	{
		return d(engine);
	}

	double RandomGen::random_double(const double& min, const double& max)
	{
		return d(engine, std::uniform_real<double>::param_type(min, max));
	}
	EngineResourceType& RandomGen::getType() const
	{
		return type;
	}
}
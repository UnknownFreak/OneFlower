#pragma once
#include "Random.hpp"
#include <Module/Globals.hpp>
of::module::EngineResourceType of::module::interface::IEngineResource<EngineModule::RandomGen>::type = of::module::EngineResourceType::RandomGen;

std::random_device EngineModule::RandomGen::rd;
std::mt19937_64 EngineModule::RandomGen::engine(EngineModule::RandomGen::rd());

namespace EngineModule
{
	RandomGen::RandomGen()
	{
		if (of::engine::GetModule<Globals>().boolGlobals[Globals::B_FORCE_SAME_SEED])
			engine.seed(0);
		else
			engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
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
	of::module::EngineResourceType& RandomGen::getType() const
	{
		return type;
	}
}
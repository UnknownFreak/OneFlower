#pragma once
#include <random>
#include <Interfaces/IEngineModule.hpp>

namespace EngineModule
{
	class RandomGen : public Interfaces::IEngineResource<RandomGen>
	{
		std::random_device rd;
		std::mt19937_64 engine;
		std::uniform_real_distribution<double> d;
		std::uniform_real_distribution<float> f;
		std::uniform_int_distribution<int> i;
	public:
		RandomGen();

		int random_int();
		int random_int(const int& min, const int& max);
		float random_float();
		float random_float(const float& min, const float& max);
		double random_double();
		double random_double(const double& min, const double& max);

		// Inherited via IEngineResource
		virtual Enums::EngineResourceType& getType() const override;
	};
}
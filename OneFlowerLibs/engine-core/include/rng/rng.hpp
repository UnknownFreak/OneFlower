#pragma once
#include <random>

namespace of::rng
{
	class RandomGen
	{
		std::uniform_real_distribution<double> d;
		std::uniform_real_distribution<float> f;
		std::uniform_int_distribution<int> i;
		std::uniform_int_distribution<unsigned int> ui;
	public:

		std::random_device rd;
		std::mt19937_64 engine;
		RandomGen();
		RandomGen& operator=(const RandomGen& ) = delete;

		int randomInt();
		int randomInt(const int min, const int max);

		float randomFloat();
		float randomFloat(const float min, const float max);
		double randomDouble();
		double randomDouble(const double min, const double max);
	};

	void init();
	void shutdown();

	RandomGen& get();

}
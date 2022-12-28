#include "AI.hpp"

namespace of::object::component
{
	void AI::onCollision(GameObject*)
	{
	}

	void AI::onMessage(const messaging::Message&)
	{
	}

	void AI::Update()
	{
	}

	void AI::Simulate(const float& fElapsedTime)
	{
		behavior->onGameTick(fElapsedTime);
	}

	void AI::onDeath()
	{
	}
}

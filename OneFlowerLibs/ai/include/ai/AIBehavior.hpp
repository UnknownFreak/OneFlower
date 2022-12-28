#pragma once


namespace of::ai
{

	class AIBehavior
	{

	public:
		virtual void onGameTick(const float& deltat) = 0;

	};

}
#pragma once

#include <utils/common/string.hpp>

#include <utils/highResolutionclock.hpp>

namespace of::timer
{

	void init();
	void shutdown();

	::utils::HighResolutionClock& get(const of::common::String& timer);
	float elapsedTime(const of::common::String& timer, const bool reset=false);
	void reset(const of::common::String& timer);
	bool passed(const of::common::String& timer, const float time);
	void remove(const of::common::String& timer);


	namespace constants
	{
		constexpr float update_ms = 1.f / 60.f;
	}
}
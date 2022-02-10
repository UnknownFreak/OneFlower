#ifndef TickTimer_HPP
#define TickTimer_HPP

#include "String.hpp"

namespace Core
{

	struct TickTimerInfo
	{
		bool started = false;
		bool finished = false;
		float maxTime;
		float currentTime;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(started);
			ar(finished);
			ar(maxTime);
			ar(currentTime);
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(started);
			ar(finished);
			ar(maxTime);
			ar(currentTime);
		}
	};

	struct TickTimer
	{
		float maxTime;
		float currentTime = 0.f;

		bool tick(const float& dt);
		bool ready() const;
		String remainingTime() const;
		void reset(const bool& hard=false);

		float getFraction() const;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(maxTime);
			ar(currentTime);
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(maxTime);
			ar(currentTime);
		}

		static TickTimer from(const TickTimerInfo& info);
		TickTimerInfo getInfo() const;

	};
}

#endif
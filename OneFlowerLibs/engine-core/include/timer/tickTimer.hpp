#pragma once

#include <courier/channelId.hpp>
#include <courier/subscriberId.hpp>
#include <courier/Topic.hpp>

#include <vector>

#include <utils/common/string.hpp>
#include <utils/lifetime/isAlive.hpp>

namespace of::timer
{

	class TickTimer : public of::utils::lifetime::IsAlive
	{
	public:
		bool started = false;
		bool finished = false;
		bool autoReset = false;
		float maxTime;
		float currentTime = 0.f;
		courier::SubscriberId timerId;
		std::vector<std::pair<courier::Topic, courier::SubscriberId>> messagesToSend;


		virtual ~TickTimer();

		void start();
		void stop();
		void reset(const bool zero=false);
		bool done() const;

		float getFraction() const;
		of::common::String remainingTime() const;
		of::common::String elapsedTime() const;

	private:

		void onFinish();

	public:

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(started);
			ar(finished);
			ar(autoReset);
			ar(maxTime);
			ar(currentTime);
		}

		template <class Archive>
		void load(Archive& ar)
		{
			stop();
			ar(started);
			ar(finished);
			ar(autoReset);

			ar(maxTime);
			ar(currentTime);

			if (started)
			{
				// tick timer wont start unless started is set to false.
				// 
				started = false;
				start();
			}

		}
	};
}
#include <timer/tickTimer.hpp>

#include <courier/courier.hpp>
#include <engine/courier/topic.hpp>
#include <engine/courier/messageType.hpp>

namespace of::timer
{

	TickTimer::~TickTimer()
	{
		stop();
	}

	void TickTimer::start()
	{
		if (started == false && finished == false)
		{
			started = true;
			using Topic = of::engine::courier::Topic;
			constexpr auto on = of::Topic::convert;

			auto& courier = courier::get();
			timerId = courier.addSubscriber(on(Topic::Update), courier::Subscriber(isAlive(), [this](const courier::Message& msg) {

				currentTime += msg.get<float>();
				finished = done();
				if (finished)
				{
					onFinish();
					if (autoReset == false)
					{
						started = false;
						auto& lambda_courier = courier::get();
						
						constexpr auto from = of::Topic::convert;

						lambda_courier.scheduleRemoval(from(Topic::Update), timerId);
					}
					else
					{
						reset();
					}
				}

			}));
		}
	}

	void TickTimer::stop()
	{
		if (started)
		{
			using Topic = of::engine::courier::Topic;
			constexpr auto from = of::Topic::convert;
			courier::get().removeSubscriber(from(Topic::Update), timerId);
			started = false;
		}
	}

	void TickTimer::reset(const bool zero)
	{
		finished = false;
		if (zero)
		{
			currentTime = 0.f;
		}
		else
		{
			currentTime -= maxTime;
			if (currentTime < 0.f)
			{
				currentTime = 0.f;
			}
		}
	}

	bool TickTimer::done() const
	{
		return currentTime > maxTime;
	}

	float TickTimer::getFraction() const
	{
		return currentTime / maxTime;
	}

	of::common::String TickTimer::remainingTime() const
	{
		return std::to_string(maxTime - currentTime);
	}

	of::common::String TickTimer::elapsedTime() const
	{
		return std::to_string(currentTime);
	}

	void TickTimer::onFinish()
	{
		auto& courier = courier::get();
		for (auto& listerner : messagesToSend)
		{
			courier.schedule(listerner.first, listerner.second, courier::Message(courier::MessageType::Notify, "TickTimer"));
		}
	}
}
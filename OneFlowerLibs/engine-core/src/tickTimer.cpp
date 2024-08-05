#include <timer/tickTimer.hpp>

#include <courier/courier.hpp>

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
			auto& courier = of::engine::GetModule<of::courier::Courier>();
			timerId = courier.addSubscriber(of::courier::Topic::Update, of::courier::Subscriber(isAlive(), [this](const of::courier::Message& msg) {

				currentTime += msg.get<float>();
				finished = done();
				if (finished)
				{
					onFinish();
					if (autoReset == false)
					{
						started = false;
						auto& lambda_courier = of::engine::GetModule<of::courier::Courier>();
						lambda_courier.scheduleRemoval(of::courier::Topic::Update, timerId);
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
			auto& courier = of::engine::GetModule<of::courier::Courier>();
			courier.removeSubscriber(of::courier::Topic::Update, timerId);
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
		auto& courier = of::engine::GetModule<of::courier::Courier>();
		for (auto& listerner : messagesToSend)
		{
			courier.schedule(listerner.first, listerner.second, of::courier::Message(of::courier::MessageType::Notify, "TickTimer"));
		}
	}
}
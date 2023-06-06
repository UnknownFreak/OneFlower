#include <messaging/courier.hpp>
#include <messaging/subscriber.hpp>
#include <iostream>

using namespace of::messaging;

struct a
{
	a()
	{
		auto& c = of::engine::GetModule<of::messaging::Courier>();
		s = std::make_shared<Subscriber>(std::bind(&a::onMessage, this, std::placeholders::_1));
		c.addSubscriber(Topic::test, s);
	}
	~a()
	{
		auto& c = of::engine::GetModule<of::messaging::Courier>();
		c.removeSubscriber(Topic::test, s->getId());
	}

private:

	void onMessage(std::shared_ptr<Message>msg)
	{
		std::cout << "From a " << s->getId().to_string() << std::endl;
	}
	std::function<void(std::shared_ptr<Message>)> f;

	std::shared_ptr<Subscriber> s;
};


struct b
{
	b()
	{
		auto& c = of::engine::GetModule<of::messaging::Courier>();
		s = std::make_shared<Subscriber>(std::bind(&b::onMessage, this, std::placeholders::_1));
		c.addSubscriber(Topic::test, s);
	}
	~b()
	{
		auto& c = of::engine::GetModule<of::messaging::Courier>();
		c.removeSubscriber(Topic::test, s->getId());
	}

private:

	void onMessage(std::shared_ptr<Message>msg)
	{
		std::cout << "From b " << s->getId().to_string() << std::endl;
	}
	std::shared_ptr<Subscriber> s;
};

using namespace of::messaging;

int main()
{
	of::messaging::Courier& c = of::engine::GetModule<of::messaging::Courier>();
	c.createChannel(Topic::test);
	a x;
	b x2;
	b x3;
	a x4;

	c.post(Topic::test, std::make_shared<Message>());
	std::cout << std::endl;
	c.post(Topic::test, std::make_shared<Message>());
	std::cout << std::endl;
	c.post(Topic::test, std::make_shared<Message>());

	system("pause");

	return 0;
}
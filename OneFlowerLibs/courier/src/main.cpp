#include <messaging/courier.hpp>

struct a
{

};


struct b
{

};

using namespace of::messaging;

int main()
{
	of::messaging::Courier c;


	c.addSubscriber(Topic::test, std::make_shared<Subscriber>());


	c.post(Topic::test, std::make_shared<Message>());

	return 0;
}
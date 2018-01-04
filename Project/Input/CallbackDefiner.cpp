#include "Callback.hpp"

Callback::Callback(Core::String callbacName, std::function<void(void)> callbackMethod) : callbackName(callbackName), callbackMethod(callbackMethod)
{
}

Callback::Callback(const Callback & copy) : callbackName(copy.callbackName), callbackMethod(copy.callbackMethod)
{
}

Callback::Callback(const Callback && rval_copy) : callbackName(rval_copy.callbackName), callbackMethod(rval_copy.callbackMethod)
{
}

Callback & Callback::operator=(const Callback & right)
{
	callbackName = right.callbackName;
	callbackMethod = right.callbackMethod;
	return *this;
}

Callback & Callback::operator=(const Callback && rval_right)
{
	callbackName = std::move(rval_right.callbackName);
	callbackMethod = std::move(rval_right.callbackMethod);
	return *this;
}

bool Callback::operator==(const Callback & right)
{
	return callbackName == right.callbackName;
}

bool Callback::operator>(const Callback & right)
{
	return callbackName > right.callbackName;
}

bool Callback::operator<(const Callback & right)
{
	return callbackName < right.callbackName;
}

void Callback::operator()() const
{
	callbackMethod();
}

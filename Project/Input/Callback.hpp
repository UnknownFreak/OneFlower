#ifndef Callback_HPP
#define Callback_HPP

#include <Core\String.hpp>
#include <functional>

struct Callback
{
	Callback(Core::String callbackName, std::function<void(void)> callbackMethod);
	Callback(const Callback& copy);
	Callback(const Callback&& rval_copy);
	Callback& operator=(const Callback& right);
	Callback& operator=(const Callback&& rval_right);

	std::function<void(void)> callbackMethod;
	Core::String callbackName;

	bool operator==(const Callback& right);
	bool operator>(const Callback& right);
	bool operator<(const Callback& right);

};


#endif



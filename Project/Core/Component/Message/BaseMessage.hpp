#pragma once
#include <Core/String.hpp>
#include <vector>
class GameObject;
class BaseMessage
{
public:
	//BaseMessage();
	//void add();
	bool permission(Core::String key);
	void encode(Core::String key);
	//std::string& process();
	Core::String msg;
	double value;
private:
	std::vector<Core::String> keys;
};
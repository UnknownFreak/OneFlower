#pragma once
#include <string>
#include <vector>
class BaseMessage
{
public:
	//BaseMessage();
	//void add();
	bool permission(std::string key);
	void encode(std::string key);
	//std::string& process();
	std::string msg;
	double value;
private:
	std::vector<std::string> keys;
};
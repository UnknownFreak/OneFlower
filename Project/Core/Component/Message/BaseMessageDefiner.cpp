#include "BaseMessage.hpp"
bool BaseMessage::permission(Core::String str)
{
	for (size_t i = 0; i < keys.size(); i++)
	{
		if (keys.at(i) == str)
			return true;
	}
	return false;
}
void BaseMessage::encode(Core::String str)
{
	keys.push_back(str);
}
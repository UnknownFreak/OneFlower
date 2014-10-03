#ifndef IBaseComponent_HPP
#define IBaseComponent_HPP
#include "BaseComponent.hpp"
template<typename>
class IBaseComponent :public BaseComponent
{
public:
	unsigned int getType()
	{
		return typeID;
	}
	static unsigned int typeID;
	
};
#endif
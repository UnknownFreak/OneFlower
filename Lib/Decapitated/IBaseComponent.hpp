#ifndef IBaseComponent_HPP
#define IBaseComponent_HPP
#include "BaseComponentTest.hpp"
template<typename>
class IBaseComponent :public BaseComponentTest
{
public:
	static unsigned int Type(void)
	{
		static const int type = GenerateID();
		return type;
	}
protected:
	//Gameobject this component currently attached to;
	GameObject* attachedOn;
};

#endif
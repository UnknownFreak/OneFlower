#ifndef OverheadComponent_HPP
#define OverheadComponent_HPP
#include "IBaseComponent.hpp"
#include "../Text/Message.hpp"
#include "../Vector.h"
class OverheadComponent : public IBaseComponent<OverheadComponent>
{
public:

	
	Message msg;
	Vector2* pos;
	OverheadComponent();
	//~OverheadComponent();
	

	void attachOn(GameObject* attachTo);
	void setPosition();
	void setPosition(Vector2 pos);
	void setPosition(double x, double y);
	bool UpdateFromEditor();

	
	
private:

	Vector2 spriteSize;
	Vector2 offset;
	

	template<class Archive>
	friend void save(Archive &ar, const OverheadComponent &overhead);
	template<class Archive>
	friend void load(Archive &ar, OverheadComponent &overehead);

};


#endif
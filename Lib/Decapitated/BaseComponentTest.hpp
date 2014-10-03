#ifndef BaseComponentTest_HPP
#define BaseComponentTest_HPP
#include <string>
class GameObject;
class BaseComponentTest
{
private:
	static unsigned int componentID;
public:
	virtual ~BaseComponentTest() = 0 {};
	static unsigned int GenerateID()
	{
		return componentID++;
	}
	//Attach the component onto a GameObject
	void attachOn(GameObject* attachTo);
	std::string getTypeName();// = 0;


protected:
	//Gameobject this component currently attached to;
	GameObject* attachedOn;
	//Name of the component
	const std::string componentName = "BaseComponent";
private:
};
#endif
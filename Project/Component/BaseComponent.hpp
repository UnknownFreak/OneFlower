#ifndef BaseComponentTest_HPP
#define BaseComponentTest_HPP

#include <string>

#include <map>

class BaseField;
class GameObject;
class BaseMessage
{
public:
	BaseMessage(std::string msg);
	std::string process();
private:
	std::string msg;
};

class BaseComponent
{
public:
	virtual ~BaseComponent() = 0
	{
	};
	//Return a Uniq classID
	virtual const unsigned int getType() = 0;// = 0;

	//Attach the component to a GameObject
	virtual void attachOn(GameObject* attachTo);

	//Copy of Registerd editor variables
	virtual std::map<std::string,BaseField*> getFields() = 0;

	//Update component whenever Editor change a variable value
	virtual bool UpdateFromEditor();

	//Return the type name
	virtual	std::string getTypeName() = 0;

	//LOW: is this needed
	//Send infomation what happend when colliding
	//void sendMessage(const BaseMessage& msg);
	//LOW: Create a body?
	//On hit collision		//TODO: Make this virtal
	void recieveMessage(const BaseMessage& target);

	//Gameobject this component currently attached to;
	GameObject* attachedOn;
protected:

	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive,const BaseComponent& bc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive,BaseComponent& bc);
};
#endif
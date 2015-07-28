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
	void add();
	std::string process();

	bool permission(std::string key);

private:
	std::string msg;
};

class BaseComponent
{
public:
	//LOW: is this needed
	//Send infomation what happend when colliding
	void sendMessage(const BaseMessage& msg);
	
	//LOW: Create a body?
	//On hit collision		//TODO: Make this virtal

	//Gameobject this component currently attached to;
	GameObject* attachedOn;

protected:
	friend class GameObject;
	virtual ~BaseComponent() = 0
	{
	};
	//Return a Uniq classID
	virtual const unsigned int getType() = 0;// = 0;


	//Return the type name
	virtual	std::string getTypeName() = 0;


	
	
	//HIGH: remove? 
	virtual void update();

	//Attach the component to a GameObject
	virtual void attachOn(GameObject* attachTo);
	
	
	void recieveMessage(const BaseMessage& target);

#ifdef _DEBUG
	friend class EngineWindow;
	friend class Prefab;

	//Copy of Registerd editor variables
	virtual std::map<std::string,BaseField*> getFields() = 0;

	
	//Update component whenever Editor change a variable value
	virtual bool UpdateFromEditor();
#endif

protected:

	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive,const BaseComponent& bc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive,BaseComponent& bc);
};
#endif
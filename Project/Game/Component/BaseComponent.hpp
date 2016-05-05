#ifndef BaseComponentTest_HPP
#define BaseComponentTest_HPP
#include "../BaseMessage.hpp"
#include <string>

#include <map>
namespace Physics{class Collider;}

class BaseField;
class GameObject;

class BaseComponent
{
public:

	//LOW: Create a body?
	//On hit collision		//TODO: Make this virtal
	virtual void onCollision(Physics::Collider);
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

	virtual void getMessage(const BaseMessage message);

#ifdef _DEBUG
	friend class EngineWindow;
	friend class Prefab;

	//Copy of Registerd editor variables
	virtual std::map<std::string,BaseField*> getFields() = 0;

	//update component whenever Editor change a variable value
	virtual bool updateFromEditor();
#endif

protected:

	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive,const BaseComponent& bc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive,BaseComponent& bc);
};
#endif
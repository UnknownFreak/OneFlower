#ifndef BaseComponentTest_HPP
#define BaseComponentTest_HPP
#include <map>
#include "Message\BaseMessage.hpp"
#include <Core\String.hpp>
namespace Physics { class Collider; }

namespace Component
{
}

class BaseField;
class GameObject;
class ComponentTypes;
class BaseComponent
{
public:

	//LOW: Create a body?
	//On hit collision		//TODO: Make this virtal
	virtual void onCollision(Physics::Collider&);
	//Gameobject this component currently attached to;
	GameObject* attachedOn = NULL;

	virtual BaseComponent* copy() const = 0;

protected:

	friend class GameObject;
	friend class ComponentTypes;

	//Return a Uniq classID
	virtual const unsigned int getType() = 0;// = 0;

	//Return the type name
	virtual	Core::String getTypeName() = 0;

	//HIGH: remove?
	virtual void update();

	//Attach the component to a GameObject
	virtual void attachOn(GameObject* attachTo);

	virtual void getMessage(const BaseMessage message);
#ifdef _DEBUG
	friend class EngineWindow;
	friend class Prefab;

	//Copy of Registerd editor variables
	//virtual std::map<std::string,BaseField*> getFields() = 0;

	//update component whenever Editor change a variable value
	virtual bool updateFromEditor();
#endif

public:
	virtual ~BaseComponent() = 0
	{
	};
	//template < class Archive>//, GameObject& go>
	//friend void save(Archive& archive, const BaseComponent& bc);
	//template < class Archive>//, GameObject& go>
	//friend void load(Archive& archive, BaseComponent& bc);
};
#endif
#ifndef BaseComponentTest_HPP
#define BaseComponentTest_HPP
#include <string>
#include <cereal\access.hpp>
class GameObject;
class BaseComponent
{
public:
	virtual ~BaseComponent() = 0 {};
	
	//Return a Uniq classID
	virtual unsigned int getType() = 0;// = 0;

	//Attach the component to a GameObject 
	void attachOn(GameObject* attachTo);

	//Return the type name
	std::string getTypeName();// = 0;

protected:
	//Name of the component
	std::string componentName;// = "BaseComponent";

	//Gameobject this component currently attached to;
	GameObject* attachedOn;

	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive,const BaseComponent& bc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive,BaseComponent& bc);
};
#endif
	#ifndef BaseComponentTest_HPP
#define BaseComponentTest_HPP

#include <string>
#include <cereal\access.hpp>

#include <map>

class BaseField;
class GameObject;
class BaseComponent
{
public:
	virtual ~BaseComponent() = 0{};
	//Return a Uniq classID
	virtual const unsigned int getType() = 0;// = 0;

	//Attach the component to a GameObject 
	void attachOn(GameObject* attachTo);

	//Copy of Registerd editor variables
	virtual std::map<std::string,BaseField*> getFields() = 0;

	//Update component whenever Editor change a variable value
	virtual bool UpdateFromEditor() ;

	//Return the type name
	virtual	std::string getTypeName() = 0;
protected:

	//Gameobject this component currently attached to;
	GameObject* attachedOn;

	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive,const BaseComponent& bc);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive,BaseComponent& bc);
};
#endif
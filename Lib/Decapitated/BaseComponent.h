#ifndef BaseComponent_H
#define BaseComponent_H
#include <string>
#include <cereal\access.hpp>
class GameObject;
class BaseComponent
{
public:
	//virtual ~BaseComponent();
	virtual	std::string getTypeName() = 0;
	//Attach the component onto a GameObject
	void attachOn(GameObject* attachTo);


protected:
	//Gameobject this component currently attached to;
	GameObject* attachedOn;
protected:
	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive, const BaseComponent& go);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive, BaseComponent& go);
	
protected:
	//Name of the component
	const std::string componentName = "BaseComponent";
private:

};

#endif
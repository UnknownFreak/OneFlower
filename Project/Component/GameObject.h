#pragma once
#ifndef GameObject_H
#define GameObject_H
#include <map>
#include <string>
#include "BaseComponent.hpp" //Remove this and use class basecomponent; 2014-04-17
#include <cereal/access.hpp>

class BaseComponent;
class GameObject
{
public:
	GameObject();
	GameObject(const GameObject & go);
	//GameObject(GameObject & go);
	GameObject(std::string _name);
	~GameObject();
	std::string name = "New GameObject";
	std::string tag = "";
	unsigned int id;

	
	template <class T,typename... Args>
	void AddComponent(Args... as)
	{
		int a = IBaseComponent<T>::typeID;
		//use map inbuild function to check if there is a
		if(!componentMap.count(IBaseComponent<T>::typeID) > 0)
		{
			BaseComponent* componentToAttach = new T(as...);
			componentToAttach->attachOn(this);
			componentMap.insert(std::make_pair(componentToAttach->getType(),componentToAttach));
		
		
		}
		
	};


	//Attach a derivied component 
	void AddComponent(BaseComponent* componentToAdd);


	template<class T_S>
	const T_S* ReadComponent()const
	{
		std::map<int,BaseComponent*>::const_iterator it;
		int a = IBaseComponent<T_S>::typeID;// a;

		it = componentMap.find(a);// .getType());

		if(it != componentMap.end())
			return 	(T_S*)it->second;

		return NULL;
	}
	
	template<class T_S>
	//Return reference pointer toward the component type
	T_S* GetComponent()
		{
			std::map<int,BaseComponent*>::iterator it;
			it = componentMap.find(IBaseComponent<T_S>::typeID);

			if(it != componentMap.end())
				return 	(T_S*)it->second;
			else
				return NULL;
		}

	std::map<int,BaseComponent*>* GetComponents() ;

	
protected:
	//std::map<std::string, BaseComponent*> componentMap;
	//List of all component that is currently attached to the GameObject
	std::map<int, BaseComponent*> componentMap;


	template < class Archive>//, GameObject& go>
	friend void save(Archive& archive,const GameObject& go);
	template < class Archive>//, GameObject& go>
	friend void load(Archive& archive,GameObject& go);

};
#endif
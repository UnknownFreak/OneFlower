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

	//Attach a derivied component 
	void AddComponent(BaseComponent* componentToAdd);
		
	//Returns a component pointer from the componentMap
	#pragma region GetComponent Non Const
	/*template<class T_S>
	T_S* GetComponent()
	{
		std::string test = typeid(T_S).name();
		std::map<std::string, BaseComponent*>::iterator it;
		
		for (int i = 0; i < 6; i++)
		{
			test.erase(test.begin());
		}
		it = componentMap.find(test);

		if (it != componentMap.end())
		{
			T_S* ptTComponent;
			ptTComponent = (T_S*)it->second;

			return ptTComponent;
		}
		else
			return NULL;
	}
	//*/


#pragma endregion
	
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
	T_S* GetComponent()
	{
			std::map<int,BaseComponent*>::iterator it;

			it = componentMap.find(IBaseComponent<T_S>::typeID);

			if(it != componentMap.end())
				return 	(T_S*)it->second;

			return NULL;
		}



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
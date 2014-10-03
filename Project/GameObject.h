#ifndef GameObject_H
#define GameObject_H
#include <map>
#include <string>
#include "Component\BaseComponent.hpp"
class GameObject
{
public:
	GameObject();
	GameObject(std::string _name);

	~GameObject();
	std::string name = "New GameObject";
	unsigned int id;

	//Attach a derivied component 
	void AddComponent(BaseComponent* componentToAdd);

	//Returns a component pointer from the componentMap
	#pragma region GetComponent Non Const
	template<class T_S>
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
	#pragma endregion
protected:
	//List of all component that is currently attached to the GameObject
	std::map<std::string,BaseComponent*> componentMap;



};
#endif
#ifndef GameObject_H
#define GameObject_H
#include <map>
#include <Core/String.hpp>
#include "BaseComponent.hpp" //Remove this and use class basecomponent; 2014-04-17
//#include "../../Physics/Collider.hpp"
//#include "../../../Game/BaseMessage.hpp" // <- included via BaseComponent
//#include <vector>
#include <memory>

namespace Physics { class Collider; }

class BaseComponent;
class GameObject
{
	friend class BaseComponent;
public:
	GameObject();
	GameObject(const GameObject & go);
	//GameObject(GameObject & go);
	GameObject(Core::String _name);
	~GameObject();
	Core::String name = "New GameObject";
	Core::String tag = "";
	unsigned int id;

	//HIGH: Make this return the adress pointer towards the newly created component
	template <class T, typename... Args>
	T* AddComponent(Args... as)
	{
		int a = IBaseComponent<T>::typeID;
		//use map inbuild function to check if there is a
		if (!componentMap.count(IBaseComponent<T>::typeID))
		{
			BaseComponent* componentToAttach = new T(as...);
			componentToAttach->attachOn(this);
			return (T*)componentToAttach;
		}
		return nullptr;
	};

	//Attach a derivied component
	BaseComponent* AddComponent(BaseComponent* componentToAdd);
	//HIGH: Remove reeadComponent? Obsolete since get Component exist

	template<class T_S>
	const T_S* ReadComponent()const
	{
		std::map<int, BaseComponent*>::const_iterator it;
		int a = IBaseComponent<T_S>::typeID;// a;

		it = componentMap.find(a);// .getType());

		if (it != componentMap.end())
			return 	(T_S*)it->second;

		return NULL;
	}
	//*/
	template<class T_S>
	//Return reference pointer toward the component type
	T_S* GetComponent()
	{
		std::map<int, BaseComponent*>::iterator it;
		it = componentMap.find(IBaseComponent<T_S>::typeID);

		if (it != componentMap.end())
			return 	(T_S*)it->second;
		else
			return NULL;
	}

	template<class T_S>
	bool RemoveComponent()
	{
		std::map<int, BaseComponent*>::iterator it;
		it = componentMap.find(IBaseComponent<T_S>::typeID);

		if (it == componentMap.end())
			return false;
		delete componentMap[IBaseComponent<T_S>::typeID];
		componentMap.erase(it);
		return true;
	}

	void destroy();

	void sendMessage(const BaseMessage msg, BaseComponent* c);
	void sendAll(const BaseMessage msg);

	void collision(std::vector<Physics::Collider>& msgs);

	std::map<int, BaseComponent*>* GetComponents();

protected:
	//std::map<std::string, BaseComponent*> componentMap;
	//List of all component that is currently attached to the GameObject
	std::map<int, BaseComponent*> componentMap;
public:
	template<class Archive>
	void save(Archive& archive) const
	{
		//if (go != NULL)
		{
			archive(name);
			archive(componentMap.size());
			for (std::map<int, BaseComponent*>::const_iterator it = componentMap.begin(); it != componentMap.end(); ++it)
			{
				archive(it->first);
				//Make directives id instead and use switches
				archive(*it->second);
			}
		}
	}
	template<class Archive>
	void load(Archive& archive)
	{
		int ID;
		int componentCount = 0;
		{
			archive(name);
			archive(componentCount);
			for (int i = 0; i < componentCount; i++)
			{
				archive(ID);
				std::unique_ptr<BaseComponent> b;
				archive(b);
				AddComponent(b.release());
			}
		}
	}
};
#endif
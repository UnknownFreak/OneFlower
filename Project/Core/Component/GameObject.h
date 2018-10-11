#ifndef GameObject_H
#define GameObject_H
#include <Asset\IObject.hpp>
#include <Core/String.hpp>
#include "BaseComponent.hpp" //Remove this and use class basecomponent; 2014-04-17
//#include "../../Physics/Collider.hpp"
//#include "../../../Game/BaseMessage.hpp" // <- included via Base
//#include <vector>
#include <map>
#include <memory>

namespace Physics { class Collider; }

namespace Component
{
class Base;
}
class GameObject : public IObject
{
	friend class Component::Base;
public:
	GameObject();
	GameObject(const GameObject & go);
	//GameObject(GameObject & go);
	GameObject(Core::String _name);
	GameObject& operator=(const GameObject& right);
	~GameObject();
	size_t id;

	template <class T, typename... Args>
	T* AddComponent(Args... as)
	{
		//use map inbuild function to check if there is a
		if (!componentMap.count(Component::IBaseComponent<T>::typeID))
		{
			Component::Base* componentToAttach = new T(as...);
			componentToAttach->attachOn(this);
			return (T*)componentToAttach;
		}
		return nullptr;
	};

	Component::Base* AddComponent(Component::Base* componentToAdd);

	template<class T_S>
	T_S* GetComponent() const
	{
		std::map<size_t, Component::Base*>::const_iterator it;
		it = componentMap.find(Component::IBaseComponent<T_S>::typeID);

		if (it != componentMap.end())
			return 	(T_S*)it->second;
		else
			return NULL;
	}

	template<class T_S>
	bool RemoveComponent()
	{
		std::map<size_t, Component::Base*>::iterator it;
		it = componentMap.find(Component::IBaseComponent<T_S>::typeID);

		if (it == componentMap.end())
			return false;
		delete componentMap[Component::IBaseComponent<T_S>::typeID];
		componentMap.erase(it);
		return true;
	}

	void destroy();

	void sendMessage(const BaseMessage msg, Component::Base* c);
	void sendAll(const BaseMessage msg);

	void collision(std::vector<Physics::Collider>& msgs);

	std::map<size_t, Component::Base*>* GetComponents();

protected:
	std::map<size_t, Component::Base*> componentMap;
public:
	template<class Archive>
	void save(Archive& archive) const
	{
		{
			archive(name);
			archive(componentMap.size());
			for (std::map<size_t, Component::Base*>::const_iterator it = componentMap.begin(); it != componentMap.end(); ++it)
			{
				archive(it->first);
				archive(*it->second);
			}
		}
	}
	template<class Archive>
	void load(Archive& archive)
	{
		size_t ID;
		size_t componentCount = 0;
		{
			archive(name);
			archive(componentCount);
			for (size_t i = 0; i < componentCount; i++)
			{
				archive(ID);
				std::unique_ptr<Component::Base> b;
				archive(b);
				AddComponent(b.release());
			}
		}
	}
};
#endif
#ifndef COMPONENT_FACTORY_HPP
#define COMPONENT_FACTORY_HPP

#include <Core/Component/BaseComponent.hpp>
#include <Core/Component/TransformComponent.hpp>
#include <Graphic/Component/RenderComponent.h>

struct ComponentFactory
{

	template<class T>
	static bool isTypeId(const size_t& id)
	{
		return id == Component::IBaseComponent<T>::typeID;
	}
	
	template <class T, class Ty>
	static Component::Base* load(Ty& ar)
	{
		T t;
		ar(t);
		return t.copy();
	}

	template <class T>
	static T* as(Component::Base* b)
	{
		return (T*)b;
	}

	template<class T>
	static Component::Base* load(T& ar)
	{
		size_t id;
		ar(id);
		if (isTypeId<Component::Transform>(id))
			return load<Component::Transform>(ar);
		else if (isTypeId<Component::RenderComponent>(id))
			return load<Component::RenderComponent>(ar);
		return nullptr;
	}

	template<class T>
	static void save(T& ar, Component::Base* const b)
	{
		ar(b->getType());
		if (isTypeId<Component::Transform>(b->getType()))
			ar(*as<Component::Transform>(b));
		else if(isTypeId<Component::RenderComponent>(b->getType()))
			ar(*as<Component::RenderComponent>(b));

	}
};

#endif
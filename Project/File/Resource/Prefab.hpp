#ifndef Prefab_HPP
#define Prefab_HPP

#include <vector>

#include <Interfaces/IRequestable.hpp>
#include <Helpers/Vector3.hpp>
#include <Object/BaseComponent.hpp>

#include <Object/Transform.hpp>

class GameObject;

class Prefab : public Interfaces::IRequestable
{

	void build(GameObject* object) const;
public:
	
	std::vector<std::unique_ptr<Component::Base>> components;
	float spawnDistance;
	bool isEditorOnly;

	Prefab();
	Prefab(const Prefab& copy);

	GameObject* createNewInstance(const Core::uuid& uuid, const Core::Vector3& pos) const;
	GameObject* createNewInstance(const Core::Vector3& pos) const;
	GameObject* createNewInstance(GameObject* parent) const;

	template <class Ar>
	void save(Ar& ar) const
	{
		ar(cereal::base_class<IRequestable>(this));
		ar(components);
		ar(spawnDistance);
		ar(isEditorOnly);
	}

	template <class Ar>
	void load(Ar& ar)
	{
		ar(cereal::base_class<IRequestable>(this));
		ar(components);
		ar(spawnDistance);
		ar(isEditorOnly);
	}


	// Inherited via IRequestable
	virtual Interfaces::TypeInfo getTrait() const override;

};

#endif 
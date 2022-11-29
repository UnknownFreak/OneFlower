#ifndef Prefab_HPP
#define Prefab_HPP

#include <cereal/cereal.hpp>

#include <vector>

#include <Helpers/Enum/ObjectState.hpp>

#include <Interfaces/IRequestable.hpp>
#include <glm/vec3.hpp>
#include <Object/BaseComponent.hpp>

#include <Object/Transform.hpp>

class GameObject;

namespace Asset::Resource
{

	class Prefab : public Interfaces::IRequestable
	{

		void build(GameObject* object, const bool& isPlayerSummon) const;
	public:
	
		std::vector<std::unique_ptr<Component::Base>> components;
		float spawnDistance;
		Enums::ObjectState objectState = Enums::ObjectState::Active;

		of::common::String tag;

		Prefab();
		Prefab(const Prefab& copy);

		GameObject* createNewInstance(const of::common::uuid& uuid, const glm::vec3& pos, const bool& isPlayerSummon=false) const;
		GameObject* createNewInstance(const glm::vec3& pos, const bool& isPlayerSummon = false) const;
		GameObject* createNewInstance(GameObject* parent, const bool& isPlayerSummon = false) const;
		void createNewPlayerInstance(GameObject& theObject);

		template <class Ar>
		void save(Ar& ar) const
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(components);
			ar(spawnDistance);
			ar(objectState);
		}

		template <class Ar>
		void load(Ar& ar)
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(components);
			ar(spawnDistance);
			ar(objectState);
		}


		// Inherited via IRequestable
		virtual Interfaces::TypeInfo getTrait() const override;

	};
}

#endif 
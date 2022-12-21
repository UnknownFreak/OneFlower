#ifndef Prefab_HPP
#define Prefab_HPP

#include <cereal/cereal.hpp>

#include <vector>

#include <Helpers/Enum/ObjectState.hpp>

#include <file/archive/Requestable.hpp>
#include <glm/vec3.hpp>
#include <object/component/BaseComponent.hpp>

#include <object/component/Transform.hpp>

namespace of::object
{
class GameObject;
}

namespace Asset::Resource
{

	class Prefab : public of::file::archive::Requestable
	{

		void build(of::object::GameObject* object, const bool& isPlayerSummon) const;
	public:
	
		std::vector<std::unique_ptr<of::object::component::Base>> components;
		float spawnDistance;
		Enums::ObjectState objectState = Enums::ObjectState::Active;

		of::common::String tag;

		Prefab();
		Prefab(const Prefab& copy);

		of::object::GameObject* createNewInstance(const of::common::uuid& uuid, const glm::vec3& pos, const bool& isPlayerSummon=false) const;
		of::object::GameObject* createNewInstance(const glm::vec3& pos, const bool& isPlayerSummon = false) const;
		of::object::GameObject* createNewInstance(of::object::GameObject* parent, const bool& isPlayerSummon = false) const;
		void createNewPlayerInstance(of::object::GameObject& theObject);

		template <class Ar>
		void save(Ar& ar) const
		{
			ar(cereal::base_class<Requestable>(this));
			ar(components);
			ar(spawnDistance);
			ar(objectState);
		}

		template <class Ar>
		void load(Ar& ar)
		{
			ar(cereal::base_class<Requestable>(this));
			ar(components);
			ar(spawnDistance);
			ar(objectState);
		}


		// Inherited via IRequestable
		virtual of::file::archive::TypeInfo getTrait() const override;

	};
}
CEREAL_REGISTER_TYPE(Asset::Resource::Prefab);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, Asset::Resource::Prefab);

#endif 
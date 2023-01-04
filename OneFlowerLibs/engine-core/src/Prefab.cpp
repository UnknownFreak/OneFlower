#include <resource/Prefab.hpp>

#include <module/Random.hpp>
#include <module/ObjectInstanceHandler.hpp>
#include <module/SaveFile.hpp>

#include <object/GameObject.hpp>
#include <object/component/Transform.hpp>


of::common::uuid of::file::archive::Trait<of::resource::Prefab>::typeId = of::common::uuid("c73721fb-5b3a-482e-b3df-183b686075ee");

namespace of::resource
{

	void Prefab::build(of::object::GameObject* object, const bool& isPlayersummon) const
	{
		object->tag = tag;
		//TODO: replace with ObjectStateSaveState
		//object->objectState = of::engine::GetModule<of::module::SaveFile>().getObjectState(object->id, objectState);
		for (auto& x : components)
			object->addOrReplace(x.get()->copy());
		auto& gameMode = of::engine::GetModule<of::module::SaveFile>().getGameMode();
		if (gameMode.tagModifiers.find(object->tag) != gameMode.tagModifiers.end())
			object->applyGameMode(gameMode.tagModifiers.at(object->tag));
		else if (isPlayersummon)
		{
			object->applyGameMode(gameMode.playerModifiers);
		}
		else
		{
			object->applyGameMode(gameMode.enemyModifiers);
		}
	}

	Prefab::Prefab() : Requestable(), spawnDistance(0.f)
	{

	}

	Prefab::Prefab(const Prefab& copy) : Requestable(copy), spawnDistance(copy.spawnDistance)
	{
		components.reserve(copy.components.size());
		for (auto& x : copy.components)
			components.push_back(x.get()->ucopy());
	}

	of::object::GameObject* Prefab::createNewInstance(const of::common::uuid& uuid, const glm::vec3& pos, const bool& isPlayerSummon) const
	{
		auto& x = of::engine::GetModule<of::module::ObjectInstanceHandler>();
		if (x.exists(uuid))
			return x.getObject(uuid);
		auto object = x.addObject(uuid);
		build(object, isPlayerSummon);
		object->onReconstruct();
		auto transform = object->get<of::object::component::Transform>();
		transform->pos = pos;
		return object;
	}

	of::object::GameObject* Prefab::createNewInstance(const glm::vec3& pos, const bool& isPlayerSummon) const
	{
		auto& x = of::engine::GetModule<of::module::ObjectInstanceHandler>();
		auto object = x.addObject();
		build(object, isPlayerSummon);
		auto transform = object->get<of::object::component::Transform>();
		transform->pos = pos;
		object->Update();
		return object;
	}

	glm::vec3 randomize(const glm::vec3& in, const float& random_direction)
	{
		auto& randGen = of::engine::GetModule<of::module::RandomGen>();

		return {
			in.x + randGen.random_float(-random_direction, random_direction),
			in.y + randGen.random_float(-random_direction, random_direction),
			in.z };
	}

	of::object::GameObject* Prefab::createNewInstance(of::object::GameObject* parent, const bool& isPlayerSummon) const
	{
		auto x = of::engine::GetModule<of::module::ObjectInstanceHandler>();
		auto object = x.addObject();
		build(object, isPlayerSummon);
		auto transform = object->get<of::object::component::Transform>();
		transform->pos = randomize(parent->get<of::object::component::Transform>()->buffered, spawnDistance);
		return object;
	}

	void Prefab::createNewPlayerInstance(of::object::GameObject& theObject)
	{
		build(&theObject, true);
	}

	of::file::archive::TypeInfo Prefab::getTrait() const
	{
		return { of::file::archive::Trait<Prefab>::typeId };
	}
}
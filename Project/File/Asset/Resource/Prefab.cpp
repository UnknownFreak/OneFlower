#include "Prefab.hpp"
#include <Module/BuildMode.hpp>
#include <Module/Random.hpp>
#include <Object/ObjectInstanceHandler.hpp>
#include <File/SaveFile.hpp>

Core::uuid Interfaces::Trait<Asset::Resource::Prefab>::typeId = Core::uuid("c73721fb-5b3a-482e-b3df-183b686075ee");

namespace Asset::Resource
{

	void Prefab::build(GameObject* object, const bool& isPlayersummon) const
	{
		object->tag = tag;
		object->objectState = Engine::GetModule<File::SaveFile>().getObjectState(object->id, objectState);;
		for (auto& x : components)
			object->AddOrReplaceComponent(x.get()->copy());
		auto& gameMode = Engine::GetModule<File::SaveFile>().getGameMode();
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

	Prefab::Prefab() : IRequestable(), spawnDistance(0.f)
	{

	}

	Prefab::Prefab(const Prefab& copy) : IRequestable(copy), spawnDistance(copy.spawnDistance)
	{
		components.reserve(copy.components.size());
		for (auto& x : copy.components)
			components.push_back(x.get()->ucopy());
	}

	GameObject* Prefab::createNewInstance(const Core::uuid& uuid, const glm::vec3& pos, const bool& isPlayerSummon) const
	{
		auto& x = Engine::GetModule<EngineModule::ObjectInstanceHandler>();
		auto object = x.addObject(uuid);
		build(object, isPlayerSummon);
		auto transform = object->getComponent<Component::Transform>();
		transform->pos = pos;
		return object;
	}

	GameObject* Prefab::createNewInstance(const glm::vec3& pos, const bool& isPlayerSummon) const
	{
		auto& x = Engine::GetModule<EngineModule::ObjectInstanceHandler>();
		auto object = x.addObject();
		build(object, isPlayerSummon);
		auto transform = object->getComponent<Component::Transform>();
		transform->pos = pos;
		object->Update();
		return object;
	}

	glm::vec3 randomize(const glm::vec3& in, const float& random_direction)
	{
		auto& randGen = Engine::GetModule<EngineModule::RandomGen>();

		return {
			in.x + randGen.random_float(-random_direction, random_direction),
			in.y + randGen.random_float(-random_direction, random_direction),
			in.z };
	}

	GameObject* Prefab::createNewInstance(GameObject* parent, const bool& isPlayerSummon) const
	{
		auto x = Engine::GetModule<EngineModule::ObjectInstanceHandler>();
		auto object = x.addObject();
		build(object, isPlayerSummon);
		auto transform = object->getComponent<Component::Transform>();
		transform->pos = randomize(parent->getComponent<Component::Transform>()->buffered, spawnDistance);
		return object;
	}

	void Prefab::createNewInstance(GameObject& theObject)
	{
		build(&theObject, false);
	}

	Interfaces::TypeInfo Prefab::getTrait() const
	{
		return { Interfaces::Trait<Prefab>::typeId };
	}
}
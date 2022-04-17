#include "Prefab.hpp"
#include <Module/BuildMode.hpp>
#include <Object/ObjectInstanceHandler.hpp>
#include <File/SaveFile.hpp>

Core::uuid Interfaces::Trait<Asset::Resource::Prefab>::typeId = Core::uuid("c73721fb-5b3a-482e-b3df-183b686075ee");

namespace Asset::Resource
{

	void Prefab::build(GameObject* object, const bool& isPlayersummon) const
	{
		object->tag = tag;
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

	GameObject* Prefab::createNewInstance(const Core::uuid& uuid, const Core::Vector3& pos, const bool& isPlayerSummon) const
	{
		if ((isEditorOnly && !Engine::GetBuildMode().isEditorBuild()) ||
			(isEditorOnly && !Engine::GetBuildMode().isDebugBuild()))
			return nullptr;
		auto& x = Engine::GetModule<EngineModule::ObjectInstanceHandler>();
		auto object = x.addObject(uuid);
		build(object, isPlayerSummon);
		auto transform = object->getComponent<Component::Transform>();
		transform->pos = pos;
		return object;
	}

	GameObject* Prefab::createNewInstance(const Core::Vector3& pos, const bool& isPlayerSummon) const
	{
		auto& x = Engine::GetModule<EngineModule::ObjectInstanceHandler>();
		auto object = x.addObject();
		build(object, isPlayerSummon);
		auto transform = object->getComponent<Component::Transform>();
		transform->pos = pos;
		object->Update();
		return object;
	}

	GameObject* Prefab::createNewInstance(GameObject* parent, const bool& isPlayerSummon) const
	{
		auto x = Engine::GetModule<EngineModule::ObjectInstanceHandler>();
		auto object = x.addObject();
		build(object, isPlayerSummon);
		auto transform = object->getComponent<Component::Transform>();
		transform->pos = parent->getComponent<Component::Transform>()->buffered.randomize(spawnDistance);
		return object;
	}

	Interfaces::TypeInfo Prefab::getTrait() const
	{
		return { Interfaces::Trait<Prefab>::typeId };
	}
}
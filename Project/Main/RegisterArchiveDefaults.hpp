#pragma once

#include <file/Handler.hpp>

#include <File/Asset/Resource/DialogTree.hpp>
#include <File/Asset/Resource/Prefab.hpp>

#include <File/Asset/Resource/Template/WorldInstance.hpp>
#include <File/Asset/Resource/Template/TileTemplate.hpp>
#include <File/Asset/Resource/Template/ColliderTemplate.hpp>

#include <Helpers/PrimitiveSaveable.hpp>

#include <Combat/Effect.hpp>
#include <Combat/Element.hpp>
#include <Combat/Skill.hpp>

#include <Quest/Quest.hpp>

inline void registerArchiveDefaults()
{
	static std::vector<std::pair<of::common::uuid, std::function<void(const of::file::archive::EntityIndex&)>>> vec;
	auto& archive = of::engine::GetModule<of::file::Handler>().archive;

	using namespace of::file::archive;
	using namespace of::file;

	vec.push_back({ Trait<Asset::Resource::DialogTree>::typeId ,
	[](const EntityIndex& index) {
		of::engine::GetModule<of::file::Handler>().archive.request<Asset::Resource::DialogTree>(FileId(index.modFile, index.ID));
	}});


	vec.push_back({ Trait<Asset::Resource::Prefab>::typeId ,
[](const EntityIndex& index) {
	of::engine::GetModule<of::file::Handler>().archive.request<Asset::Resource::Prefab>(FileId(index.modFile, index.ID));
} });

	vec.push_back({ Trait<File::Asset::Resource::Template::WorldInstance>::typeId ,
[](const EntityIndex& index) {
	of::engine::GetModule<of::file::Handler>().archive.request<File::Asset::Resource::Template::WorldInstance>(FileId(index.modFile, index.ID));
} });

	vec.push_back({ Trait<File::Asset::Resource::Template::TileChunk>::typeId ,
[](const EntityIndex& index) {
	of::engine::GetModule<of::file::Handler>().archive.request<File::Asset::Resource::Template::TileChunk>(FileId(index.modFile, index.ID));
} });

	vec.push_back({ Trait<File::Asset::Resource::Template::ColliderChunk>::typeId ,
[](const EntityIndex& index) {
	of::engine::GetModule<of::file::Handler>().archive.request<File::Asset::Resource::Template::ColliderChunk>(FileId(index.modFile, index.ID));
} });

	vec.push_back({ Trait<PrimitiveSaveable<of::common::String>>::typeId ,
[](const EntityIndex& index) {
	of::engine::GetModule<of::file::Handler>().archive.request<PrimitiveSaveable<of::common::String>>(FileId(index.modFile, index.ID));
} });

	vec.push_back({ Trait<Combat::Element>::typeId ,
[](const EntityIndex& index) {
	of::engine::GetModule<of::file::Handler>().archive.request<Combat::Element>(FileId(index.modFile, index.ID));
} });

	vec.push_back({ Trait<Combat::Effect>::typeId ,
[](const EntityIndex& index) {
	of::engine::GetModule<of::file::Handler>().archive.request<Combat::Effect>(FileId(index.modFile, index.ID));
} });

	vec.push_back({ Trait<Combat::Skill>::typeId ,
[](const EntityIndex& index) {
	of::engine::GetModule<of::file::Handler>().archive.request<Combat::Skill>(FileId(index.modFile, index.ID));
} });

	vec.push_back({ Trait<Questing::Quest>::typeId ,
[](const EntityIndex& index) {
	of::engine::GetModule<of::file::Handler>().archive.request<Questing::Quest>(FileId(index.modFile, index.ID));
} });


	archive.factory.registerDefaults(vec);

	//helpers[Interfaces::Trait<Combat::EffectProperty>::typeId] = [this](const EntityIndex& index) {
	//	ref->request<Combat::EffectProperty>(FileId(index.modFile, index.ID));
	//};
	//helpers[Interfaces::Trait<Combat::DamageEffect>::typeId] = [this](const EntityIndex& index) {
	//	ref->request<Combat::DamageEffect>(FileId(index.modFile, index.ID));
	//};
	//helpers[Interfaces::Trait<Combat::BarrierEffect>::typeId] = [this](const EntityIndex& index) {
	//	ref->request<Combat::BarrierEffect>(FileId(index.modFile, index.ID));
	//};
	//helpers[Interfaces::Trait<Combat::VisualEffect>::typeId] = [this](const EntityIndex& index) {
	//	ref->request<Combat::VisualEffect>(FileId(index.modFile, index.ID));
	//};
	//helpers[Interfaces::Trait<Combat::ModifierEffect>::typeId] = [this](const EntityIndex& index) {
	//	ref->request<Combat::ModifierEffect>(FileId(index.modFile, index.ID));
	//};
	//helpers[Interfaces::Trait<Questing::AOrBObjective>::typeId] = [this](const EntityIndex& index) {
	//	ref->request<Questing::AOrBObjective>(FileId(index.modFile, index.ID));
	//};
	//helpers[Interfaces::Trait<Questing::CollectItemObjective>::typeId] = [this](const EntityIndex& index) {
	//	ref->request<Questing::CollectItemObjective>(FileId(index.modFile, index.ID));
	//};
	//helpers[Interfaces::Trait<Questing::DefeatEnemyObjective>::typeId] = [this](const EntityIndex& index) {
	//	ref->request<Questing::DefeatEnemyObjective>(FileId(index.modFile, index.ID));
	//};
	//helpers[Interfaces::Trait<Questing::DefendObjective>::typeId] = [this](const EntityIndex& index) {
	//	ref->request<Questing::DefendObjective>(FileId(index.modFile, index.ID));
	//};
	//helpers[Interfaces::Trait<Questing::DuelObjective>::typeId] = [this](const EntityIndex& index) {
	//	ref->request<Questing::DuelObjective>(FileId(index.modFile, index.ID));
	//};
	//helpers[Interfaces::Trait<Questing::ListObjective>::typeId] = [this](const EntityIndex& index) {
	//	ref->request<Questing::ListObjective>(FileId(index.modFile, index.ID));
	//};

}
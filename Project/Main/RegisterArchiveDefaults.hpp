#pragma once

#include <asset/asset.hpp>

#include <File/Asset/Resource/DialogTree.hpp>
#include <resource/Prefab.hpp>

#include <resource/WorldInstance.hpp>

#include <Helpers/PrimitiveSaveable.hpp>

#include <combat/effect/Effect.hpp>
#include <Combat/Element.hpp>
#include <Combat/Skill.hpp>

#include <Quest/Quest.hpp>

inline void registerArchiveDefaults()
{
	static std::vector<std::pair<of::common::uuid, std::function<void(const of::asset::AssetIndex&)>>> vec;
	auto& archive = of::asset::getAssetRequestor();

	using namespace of::asset;

	vec.push_back({ Trait<Asset::Resource::DialogTree>::typeId ,
	[](const AssetIndex& index) {
		of::asset::getAssetRequestor().request<Asset::Resource::DialogTree>(AssetId(index.modFile, index.ID));
	}});

	vec.push_back({ Trait<of::resource::Prefab>::typeId ,
	[](const AssetIndex& index) {
		of::asset::getAssetRequestor().request<of::resource::Prefab>(AssetId(index.modFile, index.ID));
	} });

	vec.push_back({ Trait<of::resource::WorldInstance>::typeId ,
	[](const AssetIndex& index) {
		of::asset::getAssetRequestor().request<of::resource::WorldInstance>(AssetId(index.modFile, index.ID));
	} });

	vec.push_back({ Trait<PrimitiveSaveable<of::common::String>>::typeId ,
	[](const AssetIndex& index) {
		of::asset::getAssetRequestor().request<PrimitiveSaveable<of::common::String>>(AssetId(index.modFile, index.ID));
	} });

	vec.push_back({ Trait<of::combat::Element>::typeId ,
	[](const AssetIndex& index) {
		of::asset::getAssetRequestor().request<of::combat::Element>(AssetId(index.modFile, index.ID));
	} });

	vec.push_back({ Trait<of::combat::Effect>::typeId ,
	[](const AssetIndex& index) {
		of::asset::getAssetRequestor().request<of::combat::Effect>(AssetId(index.modFile, index.ID));
	} });

	vec.push_back({ Trait<of::combat::Skill>::typeId ,
	[](const AssetIndex& index) {
		of::asset::getAssetRequestor().request<of::combat::Skill>(AssetId(index.modFile, index.ID));
	} });

	vec.push_back({ Trait<Questing::Quest>::typeId ,
	[](const AssetIndex& index) {
		of::asset::getAssetRequestor().request<Questing::Quest>(AssetId(index.modFile, index.ID));
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
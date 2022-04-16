#ifndef RegisterRTTI_HPP
#define RegisterRTTI_HPP
#include <cereal/types/polymorphic.hpp>
#include <Interfaces/IRequestable.hpp>
#ifdef _UNITTESTS_
//#include <Tests/TestObjects.hpp>
//
//CEREAL_REGISTER_TYPE(Tests::MockedSaveable);
//CEREAL_REGISTER_TYPE(Tests::MockedSaveable2);
//
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Tests::MockedSaveable);
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Tests::MockedSaveable2);

#endif

#include <File/Resource/TileAtlas.hpp>
#include <File/Asset/Resource/DialogTree.hpp>
#include <File/Asset/Resource/Prefab.hpp>

#include <File/Asset/Resource/Template/WorldInstance.hpp>
#include <File/Asset/Resource/Template/TileTemplate.hpp>
#include <File/Asset/Resource/Template/ColliderTemplate.hpp>

#include <Graphics/Model/TextureMap.hpp>
#include <Graphics/Model/IModel.hpp>
#include <Graphics/Model/StaticModel.hpp>
#include <Graphics/Model/SpriteSheetModel.hpp>
#include <Graphics/Model/SpriterModel_.hpp>

#include <Helpers/PrimitiveSaveable.hpp>

#include <Combat/Element.hpp>
#include <Combat/Effect.hpp>
#include <Combat/EffectProperty.hpp>
#include <Combat/Skill.hpp>

#include <Object/BaseComponent.hpp>
#include <Combat/Stats.hpp>
#include <Combat/Damage.hpp>
#include <Combat/Combat.hpp>
#include <Physics/Colliders/EntityCollider.hpp>

#include <Quest/Quest.hpp>
#include <Quest/QuestObjective.hpp>
#include <Quest/AOrBObjective.hpp>
#include <Quest/CollectItemObjective.hpp>
#include <Quest/DefeatEnemyObjective.hpp>
#include <Quest/DefendObjective.hpp>
#include <Quest/DuelObjective.hpp>
#include <Quest/ListObjective.hpp>

#include <Items/Item.hpp>

CEREAL_REGISTER_TYPE(Interfaces::IRequestable);
CEREAL_REGISTER_TYPE(File::Resource::Texture::TileAtlas);
CEREAL_REGISTER_TYPE(Asset::Resource::DialogTree);
CEREAL_REGISTER_TYPE(Asset::Resource::Prefab);

CEREAL_REGISTER_TYPE(File::Asset::Resource::Template::WorldInstance);
CEREAL_REGISTER_TYPE(File::Asset::Resource::Template::TileChunk);
CEREAL_REGISTER_TYPE(File::Asset::Resource::Template::ColliderChunk);

CEREAL_REGISTER_TYPE(TextureMap);
CEREAL_REGISTER_TYPE(IModel);
CEREAL_REGISTER_TYPE(StaticModel);
CEREAL_REGISTER_TYPE(SpriteSheetModel);
CEREAL_REGISTER_TYPE(Model::SpriterModel);

CEREAL_REGISTER_TYPE(PrimitiveSaveable<Core::String>);

CEREAL_REGISTER_TYPE(Component::Base);
CEREAL_REGISTER_TYPE(Component::Stats);
CEREAL_REGISTER_TYPE(Component::Damage);
CEREAL_REGISTER_TYPE(Component::CombatComponent);
CEREAL_REGISTER_TYPE(Collider);

CEREAL_REGISTER_TYPE(Combat::Element);
CEREAL_REGISTER_TYPE(Combat::Effect);
CEREAL_REGISTER_TYPE(Combat::Skill);

CEREAL_REGISTER_TYPE(Combat::EffectProperty);
CEREAL_REGISTER_TYPE(Combat::DamageEffect);
CEREAL_REGISTER_TYPE(Combat::BarrierEffect);
CEREAL_REGISTER_TYPE(Combat::VisualEffect);
CEREAL_REGISTER_TYPE(Combat::ModifierEffect);

CEREAL_REGISTER_TYPE(Questing::Quest);
CEREAL_REGISTER_TYPE(Questing::AOrBObjective);
CEREAL_REGISTER_TYPE(Questing::CollectItemObjective);
CEREAL_REGISTER_TYPE(Questing::DefeatEnemyObjective);
CEREAL_REGISTER_TYPE(Questing::DefendObjective);
CEREAL_REGISTER_TYPE(Questing::DuelObjective);
CEREAL_REGISTER_TYPE(Questing::ListObjective);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, File::Resource::Texture::TileAtlas);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Asset::Resource::DialogTree);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Asset::Resource::Prefab);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, File::Asset::Resource::Template::WorldInstance);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, File::Asset::Resource::Template::TileChunk);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, File::Asset::Resource::Template::ColliderChunk);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, TextureMap);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, IModel);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IModel, StaticModel);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IModel, SpriteSheetModel);
CEREAL_REGISTER_POLYMORPHIC_RELATION(IModel, Model::SpriterModel);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, PrimitiveSaveable<Core::String>);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Combat::Element);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Combat::Effect);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Combat::Skill);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Combat::EffectProperty, Combat::DamageEffect);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Combat::EffectProperty, Combat::BarrierEffect);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Combat::EffectProperty, Combat::VisualEffect);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Combat::EffectProperty, Combat::ModifierEffect);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::Stats);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::Damage);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Component::CombatComponent);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component::Base, Collider);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Interfaces::IRequestable, Questing::Quest);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Questing::QuestObjective, Questing::AOrBObjective);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Questing::QuestObjective, Questing::CollectItemObjective);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Questing::QuestObjective, Questing::DefeatEnemyObjective);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Questing::QuestObjective, Questing::DefendObjective);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Questing::QuestObjective, Questing::DuelObjective);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Questing::QuestObjective, Questing::ListObjective);

#endif
#ifndef ComponentType_HPP
#define ComponentType_HPP

#include <utils/common/String.hpp>

namespace Enums
{
	enum class ComponentType
	{
// These will force the order of Update() and Simulate(const float& fElapsedTime)
// Do not change this order unless you know what's going on.
		Transform,
		Collider,
		VisionCollider, // Same as Collider but does no physics stuff only checks if collider within specific area, can be used for triggers & dialog checks.
		Render,
		Light,
		Vitality,
		Dialog,
		PlayerInteraction,
		Item,
		Inventory,
		Damage,
		Combat,
		LootDrop,
		AttachToParent, // if used the "effect" is attached to the user (e.g) a barrier with an effect)
		LootContainer,
		PlayerController,
		Activator,
		Interactable,
	};


	inline of::common::String to_string(const ComponentType& type)
	{
		switch (type)
		{
		case ComponentType::Transform: return "Transform";
		case ComponentType::Collider: return "Collider";
		case ComponentType::VisionCollider: return "VisionCollider";
		case ComponentType::Render: return "Render";
		case ComponentType::Light: return "Light";
		case ComponentType::Vitality: return "Vitality";
		case ComponentType::Dialog: return "Dialog";
		case ComponentType::PlayerInteraction: return "PlayerInteraction";
		case ComponentType::Item: return "Item";
		case ComponentType::Inventory: return "Inventory";
		case ComponentType::Damage: return "Damage";
		case ComponentType::Combat: return "Combat";
		case ComponentType::LootDrop: return "LootDrop";
		case ComponentType::AttachToParent: return "AttachToParent";
		case ComponentType::LootContainer: return "LootContainer";
		case ComponentType::PlayerController: return "PlayerController";
		case ComponentType::Activator: return "Activator";
		default:
			return "Unknown";
		}
	}
}

#endif 
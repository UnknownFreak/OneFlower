#pragma once
#ifndef Interactable_HPP
#define Interactable_HPP

#include <Helpers/Vector3.hpp>
#include "IBaseComponent.hpp"
#include "Interaction.hpp"
#include <Interfaces/ICollider.hpp>

namespace Object
{
	class GameObject;
}

namespace Component
{
	struct Interactable : public Component::IBase<Interactable>
	{

		bool interact(const Object::Interaction& interaction);

	public:

		bool canPlayerInteract;

		Core::String interactionState;

		std::unordered_map<Core::String, std::pair<Object::Interaction, Object::Interaction>> interactions;

		Interactable() = default;
		~Interactable() = default;

		virtual Interactable* copy() const override
		{
			return new Interactable(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override
		{
			return std::make_unique<Interactable>(*this);
		}

		void interact(GameObject& interactable);
		void interact(const bool& reverse, const short& repeat);

		virtual void onCollision(Interfaces::ICollider* the_collidee);
		virtual void Update() override;
		virtual void Simulate(const float& dt) override;
		virtual void onDeath() override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(canPlayerInteract);
			ar(interactionState);
			ar(interactions);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(canPlayerInteract);
			ar(interactionState);
			ar(interactions);
		}
	};
}


#endif
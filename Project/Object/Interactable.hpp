#pragma once
#ifndef Interactable_HPP
#define Interactable_HPP

#include <object/component/IBaseComponent.hpp>
#include "Interaction.hpp"

namespace of::object::component
{
	struct Interactable : public of::object::component::IBase<Interactable>
	{

		bool interact(const Object::Interaction& interaction);
		virtual void onMessage(const of::object::messaging::Message& message) override;

	public:

		bool canPlayerInteract;

		of::common::String interactionState;

		std::unordered_map<of::common::String, std::pair<Object::Interaction, Object::Interaction>> interactions;

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

		virtual void onCollision(GameObject* the_collidee);
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
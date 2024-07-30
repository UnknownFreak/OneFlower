#pragma once

#include <component/base.hpp>
#include "Interaction.hpp"

namespace of::component
{
	struct Interactable : public Base
	{

		bool interact(const Object::Interaction& interaction);

		virtual void onMessage(const of::object::messaging::Message&) override {};
		virtual void attached() override {};
		virtual void initialize() override {};
		virtual void deconstruct() override {};

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

		void interact(object::GameObject& interactable);
		void interact(const bool& reverse, const short& repeat);

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

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
		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "Interactable";
		};

		static constexpr of::common::uuid typeId = "4f6d8d08-5bec-475a-867c-5a42f3bdf285";
	};
}

#pragma once
#ifndef ObjectStateActivator_HPP
#define ObjectStateActivator_HPP

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>

#include <cereal/types/polymorphic.hpp>

#include <utils/common/uuid.hpp>
#include <object/component/IBaseComponent.hpp>
#include <object/ObjectState.hpp>

namespace of::object::component
{
	struct ObjectStateActivator : public of::object::component::IBase<ObjectStateActivator>
	{

		virtual void onMessage(const of::object::messaging::Message& message) override;

	public:
		std::vector<std::pair<of::common::uuid, Enums::ObjectState>> m_objectsToToggle;

		ObjectStateActivator() = default;
		~ObjectStateActivator() = default;

		virtual ObjectStateActivator* copy() const override
		{
			return new ObjectStateActivator(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override
		{
			return std::make_unique<ObjectStateActivator>(*this);
		}

		void toggle();

		virtual void onCollision(GameObject* the_collidee);
		virtual void Update() override;
		virtual void Simulate(const float& dt) override;
		virtual void onDeath() override;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(m_objectsToToggle);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(m_objectsToToggle);
		}
	};
}

CEREAL_REGISTER_TYPE(of::object::component::ObjectStateActivator);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::object::component::Base, of::object::component::ObjectStateActivator);

#endif
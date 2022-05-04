#pragma once
#ifndef ObjectStateActivator_HPP
#define ObjectStateActivator_HPP

#include <Helpers/Enum/ObjectState.hpp>
#include <Helpers/uuid.hpp>
#include <Helpers/Vector3.hpp>
#include "IBaseComponent.hpp"
#include <Interfaces/ICollider.hpp>

namespace Component
{
	struct ObjectStateActivator : public Component::IBase<ObjectStateActivator>
	{
	public:
		std::vector<std::pair<Core::uuid, Enums::ObjectState>> m_objectsToToggle;

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

		virtual void onCollision(Interfaces::ICollider* the_collidee);
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


#endif
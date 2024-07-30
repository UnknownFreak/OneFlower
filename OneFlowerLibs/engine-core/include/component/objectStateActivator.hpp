#pragma once
#ifndef ObjectStateActivator_HPP
#define ObjectStateActivator_HPP

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>

#include <cereal/types/polymorphic.hpp>

#include <utils/common/uuid.hpp>
#include <component/base.hpp>
#include <object/ObjectState.hpp>

namespace of::component
{
	struct ObjectStateActivator : public Base
	{

		virtual void onMessage(const of::object::messaging::Message& message) override;

		void pushObjectSaveState(const of::common::uuid& objectId, const object::ObjectState& toggle);

		virtual void deconstruct() override {};
		virtual void attached() override {};
		virtual void initialize() override {};

	public:
		std::vector<std::pair<of::common::uuid, object::ObjectState>> m_objectsToToggle;

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

		void persist(of::object::ObjectSaveState* ) override {};
		void onReconstruct(of::object::ObjectSaveState* ) override {};
		void resolveReferences() override {};

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

		of::common::uuid getType() const override
		{
			return typeId;
		};
		of::common::String getTypeName() const override
		{
			return "Activator";
		};

		static constexpr of::common::uuid typeId = "36d49da3-ef84-4856-8a1e-3bfd5fcb1898";
	};
}

CEREAL_REGISTER_TYPE(of::component::ObjectStateActivator);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::component::Base, of::component::ObjectStateActivator);

#endif
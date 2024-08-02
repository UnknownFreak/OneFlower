#pragma once

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

#include <utils/common/String.hpp>
#include <utils/common/uuid.hpp>
#include <utils/lifetime/isAlive.hpp>
#include <object/messaging/ComponentMessage.hpp>
#include <object/ObjectSaveState.hpp>

namespace of::object
{
	class GameObject;
}
namespace of::component
{
	class Base : public of::utils::lifetime::IsAlive
	{
		friend class object::GameObject;

		void attach();
		void decouple();

	public:

		object::GameObject* attachedOn = nullptr;
		size_t instanceId;

		virtual Base* copy() const = 0;
		virtual std::unique_ptr<Base> ucopy() const = 0;

	protected:

		virtual of::common::uuid getType() const = 0;
		virtual of::common::String getTypeName() const = 0;
		virtual void onMessage(const object::messaging::Message& message) = 0;

		bool post(const of::common::uuid& id, const object::messaging::Topic topic, std::shared_ptr<object::messaging::Body> message) const;
		void post(const object::messaging::Topic topic, std::shared_ptr<object::messaging::Body> message) const;
		void post(const object::messaging::Message& message) const;

	public:

		virtual void deconstruct() = 0;
		
		// TODO: move initialize from attach on, to a separate call after the entire object is built, to initialize
		// also store the base initialization status in this class.
		// this initialize should only be called by prefabs, or gameObject onBuildFinish or similar.
		virtual void initialize() = 0;
		virtual void attached() = 0;

	public:

		virtual void persist(of::object::ObjectSaveState* saveState) = 0;
		virtual void onReconstruct(of::object::ObjectSaveState* saveState) = 0;
		virtual void resolveReferences() = 0;

		virtual ~Base() = default;
		Base();
		Base(const Base& base);
	};
}

CEREAL_REGISTER_TYPE(of::component::Base);

#ifndef BaseComponentTest_HPP
#define BaseComponentTest_HPP

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

#include <utils/common/String.hpp>
#include <utils/common/uuid.hpp>
#include <object/messaging/ComponentMessage.hpp>
#include <object/ObjectSaveState.hpp>

namespace of::object
{
	class GameObject;
}
namespace of::object::component
{
	class Base
	{
		friend class GameObject;

	public:

		virtual void onCollision(GameObject* the_collidee) = 0;

		GameObject* attachedOn = nullptr;

		virtual Base* copy() const = 0;
		virtual std::unique_ptr<Base> ucopy() const = 0;

		virtual void detach() {};

		//Base(Base&&) = default;

	protected:

		virtual of::common::uuid getType() const = 0;
		virtual of::common::String getTypeName() const = 0;
		virtual void onMessage(const messaging::Message& message) = 0;


		void post(const messaging::Topic topic, std::shared_ptr<messaging::Body> message) const;
		void post(const messaging::Message& message) const;

		//HIGH: remove?
	public:
		virtual void Update() = 0;
		virtual void Simulate(const float& fElapsedTime) = 0;

		virtual void attachOn(GameObject* attachTo);

		virtual void onDeath() = 0;
		virtual void onDelete() {};

	public:

		virtual void persist(of::object::ObjectSaveState* saveState) = 0;
		virtual void onReconstruct(of::object::ObjectSaveState* saveState) = 0;
		virtual void resolveReferences() = 0;

		virtual ~Base() = default;
	};
}

CEREAL_REGISTER_TYPE(of::object::component::Base);

#endif
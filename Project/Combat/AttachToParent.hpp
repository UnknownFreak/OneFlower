#ifndef AttachToParent_HPP
#define AttachToParent_Hpp

#include <object/component/BaseComponent.hpp>

namespace of::object::component
{

	class AttachToParent : public Base
	{
		GameObject* objectToFollow;
	public:
		AttachToParent(GameObject* objectToFollow);

		// Inherited via IBase
		virtual void onCollision(GameObject* the_collidee) override;
		virtual void Update() override;
		virtual void Simulate(const float& fElapsedTime) override;
		virtual void onDeath();

		virtual void onMessage(const messaging::Message& message) override;

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

		virtual AttachToParent* copy() const override
		{
			return new AttachToParent(*this);
		};

		virtual std::unique_ptr<Base> ucopy() const override 
		{
			return std::make_unique<AttachToParent>(*this);
		};

		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "AttachToParent";
		};

		static constexpr of::common::uuid typeId = "6e45ab1c-7a29-417b-b9fb-d6db1789696b";
	};
}

#endif
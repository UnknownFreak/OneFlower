#ifndef AttachToParent_HPP
#define AttachToParent_Hpp

#include <object/component/BaseComponent.hpp>

namespace of::object::component
{

	class AttachToParent : public Base
	{
		GameObject* objectToFollow;

		virtual void onMessage(const messaging::Message& message) override;
		virtual void initialize() override;
		virtual void deconstruct() override;

	public:
		AttachToParent(GameObject* objectToFollow);

		virtual void update(const float& fElapsedTime);

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
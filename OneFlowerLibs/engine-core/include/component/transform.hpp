#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "base.hpp"

namespace of::component
{
	class Transform : public Base
	{

	protected:

		virtual void onMessage(const object::messaging::Message& message) override;

		virtual void deconstruct() override;
		virtual void initialize() override;

	public:
		float speedModifier = 1.f;
		bool moving;
		bool falling;
		float jumpSpeed = 0.f;
		glm::vec3 buffered = { 0.f, 0.f, 0.f };
		glm::vec3 pos = { 0.f, 0.f, 0.f };
		glm::vec3 rot { 0.f };
		glm::vec3 scale { 1.f };
		glm::vec2 lastDirection;
		int directionCounter = 0;
		float facingAngle = 0.f;
		Transform() = default;
		~Transform() = default;

		virtual Transform* copy() const override
		{
			return new Transform(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override
		{
			return std::make_unique<Transform>(*this);
		}

		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "Transform";
		};

		void updateTransform(std::shared_ptr<Transform> transform);

		static constexpr of::common::uuid typeId = "e6f52003-0e92-4118-8ab0-b5d54b680c81";

		void jump();
		void move(const glm::vec2 direction);
		void lookAt(const glm::vec2 direction);

		virtual void update(const float dt);

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

	};
}

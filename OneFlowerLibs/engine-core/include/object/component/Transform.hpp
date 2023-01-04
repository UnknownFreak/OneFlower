#pragma once
#ifndef Transform_HPP
#define Transform_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "BaseComponent.hpp"

namespace of::object::component
{
	class Transform : public Base
	{

	protected:
		// Inherited via IBase
		virtual void onMessage(const messaging::Message& message) override;
	public:
		float speedModifier = 1.f;
		bool moving;
		bool falling;
		float jumpSpeed = 0.f;
		glm::vec3 buffered = { 0.f, 0.f, 0.f };
		glm::vec3 pos = { 0.f, 0.f, 0.f };
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

		static constexpr of::common::uuid typeId = "e6f52003-0e92-4118-8ab0-b5d54b680c81";

		void jump();
		void move(const glm::vec2& direction);
		void lookAt(const glm::vec2& direction);

		void attachOn(GameObject* go);
		// Inherited via IBase
		virtual void onCollision(GameObject* the_collidee);
		virtual void Update() override;
		virtual void Simulate(const float& dt) override;
		virtual void onDeath() override;

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

	};
}

#endif
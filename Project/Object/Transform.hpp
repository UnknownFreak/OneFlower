#pragma once
#ifndef Transform_HPP
#define Transform_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "IBaseComponent.hpp"
#include <Interfaces/ICollider.hpp>
#include <Combat/Stats.hpp>

namespace Component
{
	struct Transform : public Component::IBase<Transform>
	{
		Component::Stats* stats = nullptr;
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

		void jump();
		void move(const glm::vec2& direction);
		void lookAt(const glm::vec2& direction);

		void attachOn(GameObject* go);
		// Inherited via IBase
		virtual void onCollision(Interfaces::ICollider* the_collidee);
		virtual void Update() override;
		virtual void Simulate(const float& dt) override;
		virtual void onDeath() override;
	};
}


#endif
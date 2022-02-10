#pragma once
#ifndef Transform_HPP
#define Transform_HPP

#include <Helpers/Vector3.hpp>
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
		Core::Vector3f buffered = { 0.f, 0.f, 0.f };
		Core::Vector3f pos = { 0.f, 0.f, 0.f };
		Core::Vector2f lastDirection;
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
		void move(const Core::Vector2f& direction);
		void lookAt(const Core::Vector2f& direction);

		void attachOn(GameObject* go);
		// Inherited via IBase
		virtual void onCollision(Interfaces::ICollider* the_collidee);
		virtual void Update() override;
		virtual void Simulate(const float& dt) override;
		virtual void onDeath() override;
	};
}


#endif
#pragma once

//*
#include <graphics/parentedRenderable.hpp>
#include <graphics/window/Window.hpp>

#include <utils/lifetime/isAlive.hpp>
#include <utils/common/uuid.hpp>

#include <physics/physics.hpp>

#include <component/Transform.hpp>
#include <vector>

namespace of::editor
{

	class Gizmo : public of::graphics::ParentedRenderable, public of::utils::lifetime::IsAlive
	{
		of::graphics::view::Camera* c;
		glm::mat4 mat = glm::mat4(0.f);

		of::common::uuid mHovering = of::common::uuid::nil();
		of::common::uuid mSelected = of::common::uuid::nil();
		of::module::physics::ColliderType collider = of::module::physics::ColliderType::Unknown;

		bool mHit = false;
		glm::vec3 colliderHitPos = glm::vec3(0.f);
		glm::vec3 actorPos = glm::vec3(0.f);
		glm::vec3 posOg = glm::vec3(0.f);

		std::shared_ptr<of::component::Transform> mTransform = std::make_shared<of::component::Transform>();

		physx::PxActor* mSelectedActor = nullptr;

		bool m_enable = true;
		std::vector<std::shared_ptr<of::component::Transform>> m_objects;

	public:

		Gizmo(std::shared_ptr<of::graphics::window::Application>& appl);

		virtual void updateFrame(const float dt) override;

		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&);

		void updateObjectTransform(std::shared_ptr<of::component::Transform> transform);

		glm::vec3* getPos();
		glm::quat getRotation();
		void setRotation(glm::quat& quat);
	};
}
//*/
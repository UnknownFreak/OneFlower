#include <internal/gizmo.hpp>
//*
#pragma warning(push, 0)
#include <glm/gtc/quaternion.hpp>
#pragma warning(pop)

#include <courier/courier.hpp>
#include <input/inputHandler.hpp>
#include <object/InstanceHandler.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <ImGuizmo.h>
#include <glm/glm.hpp>


namespace of::editor
{

	Gizmo::Gizmo(std::shared_ptr<of::graphics::window::Application>& appl) : c(m_parent->getCamera())
	{
		ImGuizmo::RecomposeMatrixFromComponents((float*)&mTransform->pos, (float*)&mTransform->rot, (float*)&mTransform->scale, (float*)&mat);
		auto& courier = of::engine::GetModule<of::courier::Courier>();

		of::engine::GetModule<of::input::InputHandler>().mouse.RegisterCallback(of::input::Callback::MouseCallback("MouseSelect",
			[&](bool, swizzle::input::Mouse, const float&) {
				of::module::physics::ObjectType hitType;
				auto& physicsHandler = of::engine::GetModule<of::module::physics::PhysicsHandler>();
				using namespace of::module::physics;
				bool hit = physicsHandler.castRay(appl->getCameraPos(), appl->getCursorRay(), colliderHitPos, actorPos, hitType
					, CollisionLayer::SWEEP_EDITOR);
				ImGuiContext& g = *ImGui::GetCurrentContext();

				if (g.HoveredWindow == nullptr && hit && (hitType.hitType == of::module::physics::ColliderType::Object || hitType.hitType == of::module::physics::ColliderType::ObjectTrigger))
				{
					auto o = of::engine::GetModule<of::object::InstanceHandler>().getObject(hitType.objectId);
					m_enable = false;

					if (o)
					{
						auto trans = o->getShared<of::component::Transform>();
						m_objects.clear();
						m_objects.push_back(trans);
						mTransform->pos = trans->pos;
						mTransform->rot = trans->rot;
						mTransform->scale = trans->scale;
					}
					m_enable = true;

				}

			}, false), swizzle::input::Mouse::RightClick, of::input::Action::Press);


		courier.addSubscriber(
			of::courier::Topic::SingleThreadUpdate,
			of::courier::Subscriber(
				0x100000, isAlive(),
				[&, appl](const of::courier::Message&)
				{
					auto& physicsHandler = of::engine::GetModule<of::module::physics::PhysicsHandler>();

					using namespace of::module::physics;

					of::module::physics::ObjectType hitType;
					mHit = physicsHandler.castRay(appl->getCameraPos(), appl->getCursorRay(), colliderHitPos, actorPos, hitType, CollisionLayer::SWEEP_EDITOR);
					if (mHit)
					{
						if (hitType.hitType == ColliderType::Object || hitType.hitType == ColliderType::ObjectTrigger)
						{
							mHovering = hitType.objectId;
							if (hitType.go)
								posOg = hitType.go->get<of::component::Transform>()->pos;
						}
						collider = hitType.hitType;
					}
					else
					{
						collider = of::module::physics::ColliderType::Unknown;
					}
					if (collider == of::module::physics::ColliderType::Unknown)
						mHovering = of::common::uuid("00000000-1111-2222-3333-7664E8019D4D");

				}
			)
		);
	}

	void Gizmo::updateFrame(const float )
	{
	}

	void Gizmo::updateObjectTransform(std::shared_ptr<of::component::Transform> transform)
	{
		m_objects[0]->updateTransform(transform);
	}

	glm::vec3* Gizmo::getPos()
	{
		return &mTransform->pos;
	}

	glm::quat Gizmo::getRotation()
	{
		return glm::quat(mTransform->rot);
	}

	void Gizmo::setRotation(glm::quat& quat)
	{
		mTransform->rot = glm::eulerAngles(quat);
	}

	void Gizmo::render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&)
	{
		if (m_enable)
		{
			if (m_objects.size() == 0)
			{

			}
			else if (m_objects.size() == 1)
			{
				// single object manipulation
				ImGuizmo::BeginFrame();

				auto viewPort = ImGui::GetWindowViewport();

				ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());

				ImGuizmo::SetRect(viewPort->Pos.x, viewPort->Pos.y, viewPort->Size.x, viewPort->Size.y);
				ImGuizmo::Enable(true);

				ImGuizmo::RecomposeMatrixFromComponents((float*)&mTransform->pos, (float*)&mTransform->rot, (float*)&mTransform->scale, (float*)&mat);

				ImGuizmo::Manipulate((float*)&c->getView(), (float*)&c->getProjection(), ImGuizmo::UNIVERSAL, ImGuizmo::MODE::LOCAL, (float*)&mat);
				ImGuizmo::DecomposeMatrixToComponents((float*)&mat, (float*)&mTransform->pos, (float*)&mTransform->rot, (float*)&mTransform->scale);
				updateObjectTransform(mTransform);
			}
			else
			{
				// multi object manipulate
			}
		}


		ImGui::Begin("GizmoThingy");
		ImGuiContext& g = *ImGui::GetCurrentContext();

		if (g.HoveredWindow == nullptr)
		{
			ImGui::Text("Free");
			if (mHit)
			{
				ImGui::Text("Hit:");
				ImGui::Text(to_string(collider));
				ImGui::Text(mHovering.to_string().c_str());
				ImGui::InputFloat3("HitPos", &colliderHitPos.x);
				ImGui::InputFloat3("ObjectPos", &actorPos.x);
				ImGui::Text("GizmoDBG:");
				ImGui::InputFloat3("transformPos", &mTransform->pos.x);
				ImGui::InputFloat3("transformRot", &mTransform->rot.x);
				ImGui::InputFloat3("transformScl", &mTransform->scale.x);
			}
			else
			{
				ImGui::Text("NoHit");
			}
		}
		else
		{
			actorPos = glm::vec3(0.f);
			ImGui::Text("Obscured");
			ImGui::Text("NoHit");
			ImGui::InputFloat3("HitPos", &colliderHitPos.x);
			ImGui::InputFloat3("ObjectPos", &actorPos.x);
		}
		ImGui::End();

	};
}
//*/
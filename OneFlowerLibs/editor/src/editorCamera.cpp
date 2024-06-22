#include <internal/editorCamera.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <swizzle/core/Input.hpp>

namespace of::editor
{
	EditorCamera::EditorCamera()
		: CameraController()
		, mTarget(0.0F)
		, mDirection(0.0F)
		, mAngleH(0.0F)
		, mAngleV(0.0F)
		, mFollow(nullptr)
	{
		mCamera->lookAt(mCamera->getPosition(), mTarget);
		rotate(0.f, -34.f);
	}

	void EditorCamera::pan(const glm::vec3 pos)
	{
		auto delta = pos - mTarget;

		delta = delta * 0.1f;

		glm::vec3 motion(delta.x, delta.y, delta.z);
		mTarget += motion;
	}

	void EditorCamera::zoom(const float zoomDelta)
	{
		if (zoomDelta == 0.f)
			return;
		mZoomConstant -= zoomDelta;
		if (mZoomConstant < 0.2f)
			mZoomConstant = 0.2f;
	}

	void EditorCamera::mouseSlideXY(float dx, float dy)
	{
		glm::vec3 xySlide = mDirection;
		xySlide.y = 0;
		glm::vec3 left = cross(mDirection, glm::vec3(0.0F, 1.0F, 0.0F));
		left = glm::normalize(left);
		mTarget += left * -dx;
		mTarget += xySlide * dy;
	}

	void EditorCamera::mouseSlide(float dx, float dy)
	{
		glm::vec3 right = glm::normalize(cross(glm::vec3(0.0F, 1.0F, 0.0F), mDirection));
		glm::vec3 up = cross(mDirection, right);
		mTarget += right * dx;
		mTarget += up * -dy;
	}

	void EditorCamera::rotate(float dx, float dy)
	{
		mAngleH -= dx;
		mAngleV -= dy;
		if (mAngleV > 89)
		{
			mAngleV = 89;
		}
		if (mAngleV < -89)
		{
			mAngleV = -89;
		}

		glm::vec3 dir = { -1.0F, 0.0F, 0.0F };

		F32 rotateRad = glm::radians(mAngleV);

		glm::mat3 rotV = glm::mat3(glm::cos(rotateRad), -glm::sin(rotateRad), 0.0f,
			glm::sin(rotateRad), glm::cos(rotateRad), 0.0f,
			0.0f, 0.0f, 1.0f);

		dir = rotV * dir;
		dir = glm::normalize(dir);

		rotateRad = glm::radians(mAngleH);
		glm::mat3 rotH = glm::mat3(glm::cos(rotateRad), 0.0f, -glm::sin(rotateRad),
			0.0f, 1.0f, 0.0f,
			glm::sin(rotateRad), 0.0f, glm::cos(rotateRad));

		dir = rotH * dir;
		mDirection = glm::normalize(dir);
	}

	void EditorCamera::follow(std::shared_ptr<of::object::component::Transform> transform, const glm::vec3&)
	{
		mFollow = transform;
	}

	void EditorCamera::update(const float&)
	{
		float dx = 0.f, dy = 0.f;
		swizzle::input::GetMouseDelta(dx, dy);
		ImGuiContext& g = *ImGui::GetCurrentContext();

		if (mFollow != nullptr)
		{
			pan(mFollow->pos);
			if (swizzle::input::IsMouseButtonPressed(swizzle::input::Mouse::MiddleClick) && g.HoveredWindow == nullptr)
			{
				rotate(dx * 0.1f, dy * 0.1f);
			}
		}
		else
		{
			if (g.HoveredWindow == nullptr)
			{

				if (swizzle::input::IsKeyPressed(swizzle::input::Keys::KeyLShift) && swizzle::input::IsMouseButtonPressed(swizzle::input::Mouse::MiddleClick))
				{
					rotate(dx * 0.1f, dy * 0.1f);
				}
				else if (swizzle::input::IsKeyPressed(swizzle::input::Keys::KeyLCtrl) && swizzle::input::IsMouseButtonPressed(swizzle::input::Mouse::MiddleClick))
				{
					mouseSlideXY(dx * 0.05f, dy * 0.05f);
				}
				else if (swizzle::input::IsMouseButtonPressed(swizzle::input::Mouse::MiddleClick))
				{
					mouseSlide(dx * 0.05f, dy * 0.05f);
				}
			}
		}

		swizzle::input::GetMouseScrollDelta(dx, dy);
		if (g.HoveredWindow == nullptr)
			zoom(dy * 1.5f);

		mZoom = { mZoomConstant, mZoomConstant, mZoomConstant };

		auto pos = mTarget + (mDirection * mZoom);


		mCamera->setPosition(pos);
		mCamera->lookAt(pos, mTarget);
	}
}
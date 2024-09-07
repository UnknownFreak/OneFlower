#pragma once

#include <graphics/view/cameraController.hpp>

#include <common/Common.hpp>
#include <component/transform.hpp>

namespace of::editor
{
	class EditorCamera : public of::graphics::view::CameraController
	{
	public:
		EditorCamera(of::graphics::view::Camera* camera);
		~EditorCamera() = default;

	private:

		void pan(const glm::vec3 pos);

		void zoom(const float zoomDelta);

		void mouseSlideXY(float dx, float dy);


		void mouseSlide(float dx, float dy);

		void rotate(float dx, float dy);

		float mZoomConstant = 10.f;
		glm::vec3 mZoom;
		glm::vec3 mTarget;
		glm::vec3 mDirection;

		F32 mAngleH;
		F32 mAngleV;

		std::shared_ptr<of::component::Transform> mFollow;

	public:

		void follow(std::shared_ptr<of::component::Transform> transform, const glm::vec3& = {});
		virtual void update(const float) override;
	};
}
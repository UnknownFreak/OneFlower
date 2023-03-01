#pragma once

#include <utils/common/uuid.hpp>

#include <graphics/view/camera.hpp>

namespace of::object::component
{
	class Transform;
}

namespace of::graphics::view
{

	class CameraController
	{
		of::common::uuid id;

	protected:

		Camera* mCamera;
		CameraController();

	public:
		virtual ~CameraController();

		virtual void follow(std::shared_ptr<of::object::component::Transform> transform, const glm::vec3& distance = {10.f, 10.f, 10.f}) = 0;

		virtual void zoom(const float& zoomDelta) = 0;

		virtual void update(const float& dt) = 0;

	};

	//class EmptyController : public CameraController
	//{
	//public:
	//	EmptyController() : CameraController() {};

	//	void zoom(const float& ) override {}
	//	void update(const float& ) override {}
	//};

}
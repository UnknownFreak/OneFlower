#pragma once

#include <utils/common/uuid.hpp>

#include <graphics/view/camera.hpp>

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
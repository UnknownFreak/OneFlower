#include <graphics/view/cameraController.hpp>
#include <module/window/WindowProxy.hpp>

#include <swizzle/core/Input.hpp>

namespace of::graphics::view
{
	CameraController::CameraController() : mCamera(of::engine::GetModule<of::module::window::WindowProxy>().get()->getCamera())
	{
	}

	CameraController::~CameraController()
	{
	}
}
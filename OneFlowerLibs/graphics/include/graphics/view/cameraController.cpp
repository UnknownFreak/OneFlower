#include <graphics/view/cameraController.hpp>
#include <module/window/WindowProxy.hpp>

namespace of::graphics::view
{
	CameraController::CameraController() : mCamera(of::engine::GetModule<of::module::window::WindowProxy>().get()->getCamera())
	{
		auto x = of::engine::GetModule<of::module::window::WindowProxy>().get();
		x->getEventListener().addListener(id.to_string(), [this](const swizzle::core::WindowEvent& evt) {
			if (evt.getEventType() == swizzle::core::WindowEventType::MouseScrollEvent)
			{
				auto& e = (const swizzle::core::MouseScrollEvent&)evt;
				zoom(float(e.mScrollY * 1.5f));
			}
			});
	}

	CameraController::~CameraController()
	{
		auto& listener = of::engine::GetModule<of::module::window::WindowProxy>().get()->getEventListener();
		listener.removeListener(id.to_string());
	}
}
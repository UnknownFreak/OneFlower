#pragma once

#include "renderLayer.hpp"

#include <utils/common/string.hpp>
#include <unordered_map>
#include <map>

#include <glm/vec3.hpp>

#include <graphics/renderable.hpp>

#include <swizzle/Swizzle.hpp>
#include <swizzle/ApplicationTemplate.hpp>
#include <ImGuiSwzzle.hpp>

#include <graphics/view/camera.hpp>
#include <graphics/view/cameraController.hpp>

#include <graphics/sky/skyBox.hpp>

namespace of::object
{
	namespace component
	{
		class Base;
	}
	class GameObject;
}

namespace of::graphics::window
{
	class Application : public sw::Application
	{

		::common::Resource<sw::gfx::Shader> mFsq;
		::common::Resource<sw::gfx::Material> mFsqMat;
		::common::Resource<sw::gfx::CommandBuffer> mUploadBuffer;
		::common::Resource<sw::gfx::CommandBuffer> mCmdBuffer;

		::common::Resource<swizzle::gfx::FrameBuffer> mImGuiFbo;
		::common::Resource<ImGuiSwizzleRenderTarget> mImGuiRenderTarget;

		of::graphics::sky::Skybox skyBox;

		std::map<RenderLayer, std::unordered_map<of::common::uuid, std::shared_ptr<Renderable>>> renderables;
		std::map<of::common::uuid, std::shared_ptr<Renderable>> imGuiRenderables;
		std::unordered_map<of::common::uuid, std::shared_ptr<Renderable>> hitBoxRenderables;

		view::PerspectiveCamera cam;
		std::shared_ptr<of::graphics::view::CameraController> camController;

		const bool& drawHitboxes;

		void setupImGui();
		void drawStats();
		void draw(const float dt);

		// Inherited via Application
		virtual void userSetup() override;
		virtual SwBool userUpdate(F32 dt) override;
		virtual void userCleanup() override;

	public:

		std::shared_ptr<of::graphics::view::CameraController> setCameraController(std::shared_ptr<of::graphics::view::CameraController> controller);

		std::thread workerThread;

		inline bool running() const
		{
			return mWindow->isVisible();
		}

		glm::vec3 getCameraPos() const;
		glm::vec3 getCursorRay();

		Application();

		// Inherited via RenderWindowHandle
		void setup();

		void setSkybox(const of::common::String& skyboxFolderName);

		void addRenderable(const RenderLayer renderLayer, const of::common::uuid& id, std::shared_ptr<Renderable> renderable);
		void updateRenderable(const RenderLayer renderLayer, const of::common::uuid& id, std::shared_ptr<Renderable> renderable);
		void removeRenderable(const of::common::uuid& id);
		U32 getWindowHeight();
		U32 getWindowWidth();

		view::Camera* getCamera();

		static void SetWindowSource(std::weak_ptr<Application> window);
		static std::weak_ptr<Application> GetWindowSource();

	private:

		static inline std::weak_ptr<Application> sWindow;

	};
}

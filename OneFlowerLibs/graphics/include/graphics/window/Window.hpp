#ifndef ONE_WINDOW_HPP
#define ONE_WINDOW_HPP

#include "renderLayer.hpp"
#include "RenderWindowHandle.hpp"

#include <utils/common/string.hpp>
#include <unordered_map>
#include <map>
#include <functional>

#include <glm/glm.hpp>

#include <swizzle/Swizzle.hpp>

#include <module/IEngineModule.hpp>

#include <graphics/view/camera.hpp>

#include <swizzle/asset2/Assets.hpp>

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
	class Application : public RenderWindowHandle, public sw::Application
	{
		// TODO: maybe not needed... rednerables has an update deltat, so we could use that option to "update" ui position in case of window resize and whatnot.
		/*
		class DynamicWindowListener : public swizzle::EventHandler<swizzle::core::WindowEvent>
		{
			std::unordered_map<of::common::String, std::function<void(const swizzle::core::WindowEvent&)>> events;
		public:
			DynamicWindowListener() = default;

			inline virtual void publishEvent(const swizzle::core::WindowEvent& evt)
			{
				for (auto& it : events)
				{
					it.second(evt);
				}
			}

			void addListener(const of::common::String& name, std::function<void(const swizzle::core::WindowEvent&)> fn)
			{
				events[name] = fn;
			}
			void removeListener(const of::common::String& name)
			{
				events.erase(name);
			}
		};

		DynamicWindowListener listener;
		DynamicWindowListener& getEventListener();

		*/

		::common::Resource<sw::gfx::Shader> mFsq;
		::common::Resource<sw::gfx::Material> mFsqMat;
		::common::Resource<sw::gfx::CommandBuffer> mUploadBuffer;
		::common::Resource<sw::gfx::CommandBuffer> mCmdBuffer;

		std::shared_ptr<Renderable> skyBox;
		//of::graphics::quadtree<Renderable> renderables;
		//std::map<of::common::uuid, std::shared_ptr<Renderable>> uiRenderables;

		std::map<RenderLayer, std::unordered_map<of::common::uuid, std::shared_ptr<Renderable>>> renderables;
		std::map<of::common::uuid, std::shared_ptr<Renderable>> imGuiRenderables;
		view::PerspectiveCamera cam;
		const bool& drawHitbox;

		void setupImGui();
		void drawStats();
		void draw(const float& dt);

		// Inherited via Application
		virtual void userSetup() override;
		virtual SwBool userUpdate(F32 dt) override;
		virtual void userCleanup() override;

	public:

		Application();

		// Inherited via RenderWindowHandle
		virtual void setup() override;
		virtual void loop() override;
		virtual void cleanup() override;
		virtual void addRenderable(const RenderLayer& renderLayer, const of::common::uuid& id, std::shared_ptr<Renderable> renderable) override;
		virtual void updateRenderable(const RenderLayer& renderLayer, const of::common::uuid& id, std::shared_ptr<Renderable> renderable) override;
		virtual void removeRenderable(const of::common::uuid& id) override;
		virtual U32 getWindowHeight() override;
		virtual U32 getWindowWidth() override;

		view::PerspectiveCamera& getCamera();

	};
}

#endif //WINDOW_HPP
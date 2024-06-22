#pragma once

#include <thread>

#include <swizzle/core/Event.hpp>
#include <swizzle/core/WindowEvents.hpp>

#include <graphics/window/renderLayer.hpp>
#include <graphics/renderable.hpp>
#include <utils/common/uuid.hpp>

#include <graphics/view/camera.hpp>
#include <graphics/view/cameraController.hpp>

namespace of::graphics::window
{

	class RenderWindowHandle
	{

	protected:

		void start()
		{
			setup();
			loop();
			cleanup();
		};

		void startDetached()
		{
			std::thread(&RenderWindowHandle::start, this).detach();
		};

		void startBlocked()
		{
			std::thread(&RenderWindowHandle::start, this).join();
		};

	public:

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

		std::shared_ptr<of::graphics::view::CameraController> camController;
		DynamicWindowListener listener;
		DynamicWindowListener& getEventListener() { return listener; };

		virtual void setup() = 0;
		virtual void loop() = 0;
		virtual void cleanup() = 0;
		
		virtual ~RenderWindowHandle() = default;

		virtual void addRenderable(const RenderLayer& renderLayer, const of::common::uuid& id, std::shared_ptr<Renderable> renderable) = 0;
		virtual void updateRenderable(const RenderLayer& renderLayer, const of::common::uuid& id, std::shared_ptr<Renderable> renderable) = 0;
		virtual void removeRenderable(const of::common::uuid& id) = 0;
		
		virtual U32 getWindowHeight() = 0;
		virtual U32 getWindowWidth() = 0;

		virtual of::graphics::view::Camera* getCamera() = 0;
		std::shared_ptr<of::graphics::view::CameraController> setCameraController(std::shared_ptr<of::graphics::view::CameraController> controller)
		{
			auto prev = camController;
			camController = controller;
			return prev;
		}

		template<class T, typename ...Args>
		requires std::derived_from<T, RenderWindowHandle> &&
		std::constructible_from<T, Args...>
		void createWindowBackgroundThread(Args&&... args)
		{
			std::shared_ptr<T> p = std::make_shared<T>(std::move<Args>(args)...);
			p->startDetached();
		}

		template<class T, typename ...Args>
			requires std::derived_from<T, RenderWindowHandle>&&
		std::constructible_from<T, Args...>
			void createWindowBlocking(Args&&... args)
		{
			std::shared_ptr<T> p = std::make_shared<T>(std::move<Args>(args)...);
			p->startBlocked();
		}
	};
}
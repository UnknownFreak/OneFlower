#pragma once

#include <graphics/window/renderLayer.hpp>
#include <graphics/renderable.hpp>
#include <utils/common/uuid.hpp>

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

		virtual void setup() = 0;
		virtual void loop() = 0;
		virtual void cleanup() = 0;
		
		virtual ~RenderWindowHandle() = default;

		virtual void addRenderable(const RenderLayer& renderLayer, const of::common::uuid& id, std::shared_ptr<Renderable> renderable) = 0;
		virtual void updateRenderable(const RenderLayer& renderLayer, const of::common::uuid& id, std::shared_ptr<Renderable> renderable) = 0;
		virtual void removeRenderable(const of::common::uuid& id) = 0;
		
		virtual U32 getWindowHeight() = 0;
		virtual U32 getWindowWidth() = 0;

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
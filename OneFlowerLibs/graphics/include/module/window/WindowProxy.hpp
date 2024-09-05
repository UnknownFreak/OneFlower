#pragma once

#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>
#include <memory>
#include <graphics/window/Window.hpp>

namespace of::module::window
{
	class WindowProxy : public of::module::interface::IEngineResource<WindowProxy>
	{
		std::shared_ptr<of::graphics::window::Application> m_handle = nullptr;
	public:

		inline WindowProxy() : WindowProxy(nullptr) {};
		inline WindowProxy(const std::shared_ptr<of::graphics::window::Application>& handle) : m_handle(handle) {};

		inline void setHandle(const std::shared_ptr<of::graphics::window::Application>& handle)
		{
			m_handle = handle;
		};

		inline of::graphics::window::Application* get() { return m_handle.get(); };
		inline operator bool() const { return m_handle.operator bool(); };

		// Inherited via IEngineResource
		virtual of::module::EngineResourceType& getType() const override;
	};
}
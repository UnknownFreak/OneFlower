#ifndef GraphicsProxy_HPP
#define GraphicsProxy_HPP

#include <memory>

#include <module/IEngineModule.hpp>
#include <swizzle/gfx/Context.hpp>
#include <swizzle/gfx/CommandBuffer.hpp>
#include <swizzle/gfx/Swapchain.hpp>


namespace OneFlower::Module::Window
{
	class Proxy : public Interface::IEngineResource<Proxy>
	{
	private:

		std::shared_ptr<swizzle::gfx::GfxContext> m_gfxContext;
		std::shared_ptr<swizzle::gfx::CommandBuffer> m_cmdBuffer;
		std::shared_ptr<swizzle::gfx::CommandBuffer> m_uploadBuffer;
		std::shared_ptr<swizzle::gfx::Swapchain> m_swapChain;
	public:

		Proxy();

		void setProxy(std::shared_ptr<swizzle::gfx::GfxContext> gfx, std::shared_ptr<swizzle::gfx::CommandBuffer> cmdBuf, std::shared_ptr<swizzle::gfx::CommandBuffer> upload,
			std::shared_ptr<swizzle::gfx::Swapchain> swapChain);

		std::shared_ptr<swizzle::gfx::GfxContext> getGfxContext();
		std::shared_ptr<swizzle::gfx::CommandBuffer> getCommandBuffer();
		std::shared_ptr<swizzle::gfx::CommandBuffer> getUploadBuffer();
		std::shared_ptr<swizzle::gfx::Swapchain> getSwapchain();

		EngineResourceType& getType() const override;
	};
}

#endif
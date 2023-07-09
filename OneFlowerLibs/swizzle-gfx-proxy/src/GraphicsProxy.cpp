#include <module/window/GraphicsProxy.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::module::window::Proxy>::type = of::module::EngineResourceType::WindowProxy;


namespace of::module::window
{
	Proxy::Proxy() {}

	void Proxy::setProxy(std::shared_ptr<swizzle::gfx::GfxContext> gfx, std::shared_ptr<swizzle::gfx::CommandBuffer> cmdBuf, std::shared_ptr<swizzle::gfx::CommandBuffer> upload,
		std::shared_ptr<swizzle::gfx::Swapchain> swapChain, std::shared_ptr<swizzle::gfx::GfxDevice> device)
	{
		m_gfxContext = gfx;
		m_cmdBuffer = cmdBuf;
		m_uploadBuffer = upload;
		m_swapChain = swapChain;
		m_gfxDeivice = device;
	}

	std::shared_ptr<swizzle::gfx::GfxDevice> Proxy::getGfxDevice() {
		return m_gfxDeivice;
	}

	std::shared_ptr<swizzle::gfx::GfxContext> Proxy::getGfxContext() {
		return m_gfxContext;
	}
	std::shared_ptr<swizzle::gfx::CommandBuffer> Proxy::getCommandBuffer() {
		return m_cmdBuffer;
	}
	std::shared_ptr<swizzle::gfx::CommandBuffer> Proxy::getUploadBuffer() {
		return m_uploadBuffer;
	}
	std::shared_ptr<swizzle::gfx::Swapchain> Proxy::getSwapchain()
	{
		return m_swapChain;
	}

	EngineResourceType& Proxy::getType() const
	{
		return type;
	}
};

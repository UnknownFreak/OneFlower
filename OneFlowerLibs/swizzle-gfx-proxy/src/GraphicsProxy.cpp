#include <module/window/GraphicsProxy.hpp>

OneFlower::Module::EngineResourceType OneFlower::Module::Interface::IEngineResource<OneFlower::Module::Window::Proxy>::type = OneFlower::Module::EngineResourceType::WindowProxy;


namespace OneFlower::Module::Window
{
	Proxy::Proxy() {}

	void Proxy::setProxy(std::shared_ptr<swizzle::gfx::GfxContext> gfx, std::shared_ptr<swizzle::gfx::CommandBuffer> cmdBuf, std::shared_ptr<swizzle::gfx::CommandBuffer> upload,
		std::shared_ptr<swizzle::gfx::Swapchain> swapChain)
	{
		m_gfxContext = gfx;
		m_cmdBuffer = cmdBuf;
		m_uploadBuffer = upload;
		m_swapChain = swapChain;
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

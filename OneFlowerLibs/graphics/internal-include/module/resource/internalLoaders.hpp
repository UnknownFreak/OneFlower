#pragma once

#include <memory>
#include <swizzle/gfx/GfxDevice.hpp>
#include <swizzle/gfx/Swapchain.hpp>
#include <swizzle/gfx/CommandBuffer.hpp>

namespace of::module
{

	namespace mesh
	{
		void init(std::weak_ptr<swizzle::gfx::GfxDevice> gfxDevice);
		void shutdown();
	}
	namespace shader
	{
		void init(std::weak_ptr<swizzle::gfx::GfxDevice> gfxDevice, std::weak_ptr<swizzle::gfx::Swapchain> swapchain);
		void shutdown();
	}
	namespace texture
	{
		void init(std::weak_ptr<swizzle::gfx::GfxDevice> gfxDevice, std::weak_ptr<swizzle::gfx::CommandBuffer> commandBuffer);
		void shutdown();
	}

}

namespace of::gfx
{
	void init(std::weak_ptr<swizzle::gfx::GfxDevice> gfxDevice);
}
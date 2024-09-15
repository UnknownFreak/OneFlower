#include <gfx/buffer.hpp>
#include <module/resource/internalLoaders.hpp>

#include <swizzle/gfx/GfxDevice.hpp>

namespace of::gfx
{
	static std::weak_ptr<swizzle::gfx::GfxDevice> g_gfxDevice{};

	void init(std::weak_ptr<swizzle::gfx::GfxDevice> gfxDevice)
	{
		g_gfxDevice = gfxDevice;
	}

	std::shared_ptr<swizzle::gfx::GfxBuffer> createBuffer(swizzle::gfx::GfxBufferType bufferType, swizzle::gfx::GfxMemoryArea memoryArea)
	{
		if (auto valid = g_gfxDevice.lock())
		{
			return valid->createBuffer(bufferType, memoryArea);
		}
		return nullptr;
	}
}
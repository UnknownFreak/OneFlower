#pragma once

#include <swizzle/gfx/GfxBuffer.hpp>
#include <swizzle/gfx/GfxTypes.hpp>

namespace of::gfx
{
	std::shared_ptr<swizzle::gfx::GfxBuffer> createBuffer(swizzle::gfx::GfxBufferType, swizzle::gfx::GfxMemoryArea);
}
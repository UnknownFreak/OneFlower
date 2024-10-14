#pragma once

#include <swizzle/asset2/Assets.hpp>
#include <swizzle/gfx/GfxBuffer.hpp>

namespace of::gfx
{
	struct Mesh
	{
		std::shared_ptr<swizzle::asset2::IMeshAsset> meshAsset;
		std::shared_ptr<swizzle::gfx::GfxBuffer> mMeshBuffer;
		std::shared_ptr<swizzle::gfx::GfxBuffer> mIndexBuffer;
		std::shared_ptr<swizzle::gfx::GfxBuffer> mBoneBuffer;
	};
}
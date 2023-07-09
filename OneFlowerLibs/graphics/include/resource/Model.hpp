#pragma once

#include <memory>

#include <swizzle/gfx/Texture.hpp>
#include <swizzle/gfx/Material.hpp>
#include <swizzle/asset2/Assets.hpp>

namespace of::resource
{
	struct Model
	{
		std::shared_ptr<swizzle::gfx::Texture> texture;
		std::shared_ptr<swizzle::gfx::Material> material;
		std::shared_ptr<swizzle::gfx::Shader> shader;
		std::shared_ptr<swizzle::asset2::IMeshAsset> mesh;
		std::shared_ptr<swizzle::gfx::GfxBuffer> mMeshBuffer;
		std::shared_ptr<swizzle::gfx::GfxBuffer> mIndexBuffer;
		std::shared_ptr<swizzle::gfx::GfxBuffer> mBoneBuffer;
	};
}
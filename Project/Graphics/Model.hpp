#pragma once

#include <memory>

#include <swizzle/gfx/Texture.hpp>
#include <swizzle/gfx/Material.hpp>
#include <swizzle/asset/MeshLoader.hpp>

namespace Graphics
{
	struct Model
	{
		std::shared_ptr<swizzle::gfx::Texture> texture;
		std::shared_ptr<swizzle::gfx::Material> material;
		std::shared_ptr<swizzle::gfx::Shader> shader;
		swizzle::Mesh mesh;
	};
}
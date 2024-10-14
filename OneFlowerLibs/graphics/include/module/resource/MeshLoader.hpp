#pragma once

#include <swizzle/asset2/Assets.hpp>

#include <swizzle/gfx/GfxDevice.hpp>

#include <utils/common/string.hpp>
#include <map>
#include <mutex>

#include <engine/paths.hpp>

#include <gfx/mesh.hpp>

#include <graphics/model/Model.hpp>

namespace of::module::mesh
{

		class Loader
	{
		bool lastResult = false;
		std::mutex mtx;
		const common::String missingMesh = "missingMesh.swm";

		std::weak_ptr<swizzle::gfx::GfxDevice> mGfxDev;

		std::map<std::pair<common::String, bool>, std::weak_ptr<of::gfx::Mesh>> mLoadedModels;

		std::shared_ptr<of::gfx::Mesh> loadMesh(const common::String& name, const bool collisionModel, swizzle::asset2::MeshAssetLoaderDescription desc);

	public:

		Loader(std::weak_ptr<swizzle::gfx::GfxDevice> gfxDev);
		Loader& operator=(const Loader&) = delete;

		std::shared_ptr<of::gfx::Mesh> requestModel(const common::String& name, const common::String& path = engine::path::meshes, const bool collisionModel=false);

		bool getResult();

		void requestRemovalOfModel(const common::String& name, const common::String&path = engine::path::meshes, const bool collisionModel=false);

	};

	Loader& get();
}

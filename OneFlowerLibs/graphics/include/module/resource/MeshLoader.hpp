#pragma once

#include <swizzle/asset2/Assets.hpp>

#include <swizzle/gfx/GfxDevice.hpp>

#include <utils/common/string.hpp>
#include <map>
#include <mutex>

#include <engine/paths.hpp>

#include <graphics/model/Model.hpp>

namespace of::module::mesh
{
	class Loader
	{
		bool lastResult = false;
		std::mutex mtx;
		const common::String missingMesh = "missingMesh.swm";

		std::weak_ptr<swizzle::gfx::GfxDevice> mGfxDev;

		std::map<std::pair<common::String, bool>, of::resource::Model> mLoadedModels;

		bool loadMesh(std::shared_ptr<swizzle::asset2::IMeshAsset>& outMeshAsset, const common::String& name, swizzle::asset2::MeshAssetLoaderDescription desc);

	public:

		Loader(std::weak_ptr<swizzle::gfx::GfxDevice> gfxDev);
		Loader& operator=(const Loader&) = delete;

		of::resource::Model requestModel(const common::String& name, const common::String& path = engine::path::meshes, const bool collisionModel=false);

		bool getResult();

		void requestRemovalOfModel(const common::String& name, const common::String&path = engine::path::meshes, const bool collisionModel=false);

	};

	Loader& get();
}

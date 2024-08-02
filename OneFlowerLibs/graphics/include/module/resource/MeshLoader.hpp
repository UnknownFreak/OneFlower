#ifndef MeshLoader_HPP
#define MeshLoader_HPP

#include <swizzle/asset2/Assets.hpp>

#include <utils/common/string.hpp>
#include <unordered_map>
#include <mutex>

#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>
#include <engine/paths.hpp>

#include <graphics/model/Model.hpp>

namespace of::module::mesh
{
	class Loader : public interface::IEngineResource<Loader>
	{
		bool lastResult = false;
		std::mutex mtx;
		const common::String missingMesh = "missingMesh.swm";

		std::map<std::pair<common::String, bool>, of::resource::Model> mLoadedModels;

		bool loadMesh(std::shared_ptr<swizzle::asset2::IMeshAsset>& outMeshAsset, const common::String& name, swizzle::asset2::MeshAssetLoaderDescription desc);

	public:

		of::resource::Model requestModel(const common::String& name, const common::String& path = engine::path::meshes, const bool collisionModel=false);

		bool getResult();

		void requestRemovalOfModel(const common::String& name, const common::String&path = engine::path::meshes, const bool collisionModel=false);

		EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
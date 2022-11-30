#ifndef MeshLoader_HPP
#define MeshLoader_HPP

#include <swizzle/asset2/Assets.hpp>

#include <utils/common/string.hpp>
#include <module/settings/EngineSettings.hpp>
#include <unordered_map>
#include <mutex>

#include <module/IEngineModule.hpp>

namespace of::module::mesh
{
	class Loader : public interface::IEngineResource<Loader>
	{
		bool lastResult = false;
		std::mutex mtx;
		const common::String missingMesh = "missingMesh.swm";
		std::unordered_map<common::String, std::shared_ptr<swizzle::asset2::IMeshAsset>> loadedMeshes;
		bool loadMesh(const common::String& name);

	public:
		std::shared_ptr<swizzle::asset2::IMeshAsset> requestMesh(const common::String& name, const common::String& path = Settings::meshPath);
		bool getResult();

		void requestRemovalOfMesh(const common::String& name);

		EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
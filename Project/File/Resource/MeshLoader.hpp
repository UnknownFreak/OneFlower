#ifndef MeshLoader_HPP
#define MeshLoader_HPP

#include <swizzle/asset2/Assets.hpp>

#include <utils/common/string.hpp>
#include <Module/Globals.hpp>
#include <unordered_map>
#include <mutex>

#include <Interfaces/IEngineModule.hpp>

namespace File::Resource::Mesh
{
	class Loader : public Interfaces::IEngineResource<Loader>
	{
		bool lastResult = false;
		std::mutex mtx;
		const of::common::String missingMesh = "missingMesh.swm";
		std::unordered_map<of::common::String, std::shared_ptr<swizzle::asset2::IMeshAsset>> loadedMeshes;
		bool loadMesh(const of::common::String& name);

	public:
		std::shared_ptr<swizzle::asset2::IMeshAsset> requestMesh(const of::common::String& name, const of::common::String& path = Globals::meshPath);
		bool getResult();

		void requestRemovalOfMesh(const of::common::String& name);

		Enums::EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
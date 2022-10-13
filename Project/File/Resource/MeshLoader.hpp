#ifndef MeshLoader_HPP
#define MeshLoader_HPP

#include <swizzle/asset2/Assets.hpp>

#include <Helpers/String.hpp>
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
		const Core::String missingMesh = "missingMesh.swm";
		std::unordered_map<Core::String, std::shared_ptr<swizzle::asset2::IMeshAsset>> loadedMeshes;
		bool loadMesh(const Core::String& name);

	public:
		std::shared_ptr<swizzle::asset2::IMeshAsset> requestMesh(const Core::String& name, const Core::String& path = Globals::meshPath);
		bool getResult();

		void requestRemovalOfMesh(const Core::String& name);

		Enums::EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
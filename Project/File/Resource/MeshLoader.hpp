#ifndef MeshLoader_HPP
#define MeshLoader_HPP

#include <swizzle/asset/MeshLoader.hpp>

#include <Helpers/String.hpp>
#include <Module/Globals.hpp>
#include <unordered_map>
#include <mutex>

#include <Interfaces/IEngineModule.hpp>

namespace File::Resource::Mesh
{
	class Loader : public Interfaces::IEngineResource<Loader>
	{
		std::mutex mtx;
		const Core::String missingMesh = "missingMesh.png";
		std::unordered_map<Core::String, std::shared_ptr<swizzle::Mesh>> loadedMeshes;
		bool loadMesh(const Core::String& name);

	public:
		std::shared_ptr<swizzle::Mesh>& requestMesh(const Core::String& name, const Core::String& path = Globals::meshPath);

		void requestRemovalOfMesh(const Core::String& name);

		Enums::EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
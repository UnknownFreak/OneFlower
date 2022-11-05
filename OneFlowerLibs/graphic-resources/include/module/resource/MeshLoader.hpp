#ifndef MeshLoader_HPP
#define MeshLoader_HPP

#include <swizzle/asset2/Assets.hpp>

#include <core/String.hpp>
#include <module/settings/EngineSettings.hpp>
#include <unordered_map>
#include <mutex>

#include <module/IEngineModule.hpp>

namespace OneFlower::Module::Mesh
{
	class Loader : public Interface::IEngineResource<Loader>
	{
		bool lastResult = false;
		std::mutex mtx;
		const Core::String missingMesh = "missingMesh.swm";
		std::unordered_map<Core::String, std::shared_ptr<swizzle::asset2::IMeshAsset>> loadedMeshes;
		bool loadMesh(const Core::String& name);

	public:
		std::shared_ptr<swizzle::asset2::IMeshAsset> requestMesh(const Core::String& name, const Core::String& path = Settings::meshPath);
		bool getResult();

		void requestRemovalOfMesh(const Core::String& name);

		EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
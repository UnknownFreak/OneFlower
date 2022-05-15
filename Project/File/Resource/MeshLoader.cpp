#include "MeshLoader.hpp"

#include <Module\EngineModuleManager.hpp>
#include <Graphics/Window.hpp>
#include <filesystem>

Enums::EngineResourceType Interfaces::IEngineResource<File::Resource::Mesh::Loader>::type = Enums::EngineResourceType::MeshLoader;

namespace File::Resource::Mesh
{
	bool Loader::loadMesh(const Core::String& name)
	{
		Core::String path = "Data/" + name;
		if (!std::filesystem::exists(path))
		{
			auto& logger = Engine::GetModule <EngineModule::Logger::OneLogger>().getLogger("File::Resource::Mesh::Loader");
			logger.Error("Unable to load mesh [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
			return false;
		}
#ifdef _DEBUG
		//MessageBox(0,"Error loading this file",name.c_str(),MB_OK);
#endif
		mtx.lock();
		auto& wnd = Engine::GetModule<Graphics::RenderWindow>();
		loadedMeshes.insert(std::make_pair(name, swizzle::asset::LoadMesh(wnd.getGfxContext(), path.c_str(), true)));
		mtx.unlock();
		return true;
	}

	swizzle::Mesh Loader::requestMesh(const Core::String& name, const Core::String& path)
	{
		if (!name.empty())
		{
			std::unordered_map<Core::String, swizzle::Mesh>::iterator it;
			it = loadedMeshes.find(path + name);
			lastResult = true;
			if (it != loadedMeshes.end())
				return it->second;

			if (loadMesh(path + name))
				return loadedMeshes.find(path + name)->second;

			//LOW set propper texturename
			it = loadedMeshes.find(Globals::meshPath + missingMesh);
			lastResult = false;
			if (it != loadedMeshes.end())
				return it->second;
			loadMesh(Globals::meshPath + missingMesh);
			return loadedMeshes.find(Globals::meshPath + missingMesh)->second;
		}
		return requestMesh(missingMesh, Globals::meshPath);
	}

	bool Loader::getResult()
	{
		return lastResult;
	}

	void Loader::requestRemovalOfMesh(const Core::String& name)
	{
		if (loadedMeshes.find(name) != loadedMeshes.end())
		{
			auto& logger = Engine::GetModule <EngineModule::Logger::OneLogger>().getLogger("File::Resource::Mesh::Loader");
			logger.Info("Unloading mesh " + name, logger.fileInfo(__FILE__, __LINE__));
			loadedMeshes.erase(name);
		}
	}

}
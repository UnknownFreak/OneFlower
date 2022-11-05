#include <module/resource/MeshLoader.hpp>

#include <Module\ModuleManager.hpp>
#include <module/logger/OneLogger.hpp>

#include <filesystem>

OneFlower::Module::EngineResourceType OneFlower::Module::Interface::IEngineResource<OneFlower::Module::Mesh::Loader>::type = OneFlower::Module::EngineResourceType::MeshLoader;

namespace OneFlower::Module::Mesh
{

	bool Loader::loadMesh(const Core::String& name)
	{
		Core::String path = "Data/" + name;
		if (!std::filesystem::exists(path))
		{
			auto& logger = Engine::GetModule <Logger::OneLogger>().getLogger("File::Resource::Mesh::Loader");
			logger.Error("Unable to load mesh [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
			return false;
		}
#ifdef _DEBUG
		//MessageBox(0,"Error loading this file",name.c_str(),MB_OK);
#endif
		mtx.lock();
		swizzle::asset2::MeshAssetLoaderDescription ldi = {};
		ldi.mLoadPossitions = {
			{swizzle::asset2::AttributeTypes::VertexPosition, 0u},
			{swizzle::asset2::AttributeTypes::NormalVector, sizeof(float) * 3u},
			{swizzle::asset2::AttributeTypes::UvCoordinates, sizeof(float) * 6u},
			{swizzle::asset2::AttributeTypes::BoneIndices, sizeof(float) * 8u},
			{swizzle::asset2::AttributeTypes::BoneWeights, sizeof(float) * 12u},
		};
		loadedMeshes.insert(std::make_pair(name, swizzle::asset2::LoadMesh(path.c_str(), ldi)));
		mtx.unlock();
		return true;
	}

	std::shared_ptr<swizzle::asset2::IMeshAsset> Loader::requestMesh(const Core::String& name, const Core::String& path)
	{
		if (!name.empty())
		{
			std::unordered_map<Core::String, std::shared_ptr<swizzle::asset2::IMeshAsset>>::iterator it;
			it = loadedMeshes.find(path + name);
			lastResult = true;
			if (it != loadedMeshes.end())
				return it->second;

			if (loadMesh(path + name))
				return loadedMeshes.find(path + name)->second;

			//LOW set propper texturename
			it = loadedMeshes.find(Settings::meshPath + missingMesh);
			lastResult = false;
			if (it != loadedMeshes.end())
				return it->second;
			loadMesh(Settings::meshPath + missingMesh);
			return loadedMeshes.find(Settings::meshPath + missingMesh)->second;
		}
		return requestMesh(missingMesh, Settings::meshPath);
	}

	bool Loader::getResult()
	{
		return lastResult;
	}

	void Loader::requestRemovalOfMesh(const Core::String& name)
	{
		if (loadedMeshes.find(name) != loadedMeshes.end())
		{
			auto& logger = Engine::GetModule <Logger::OneLogger>().getLogger("File::Resource::Mesh::Loader");
			logger.Info("Unloading mesh " + name, logger.fileInfo(__FILE__, __LINE__));
			loadedMeshes.erase(name);
		}
	}

}
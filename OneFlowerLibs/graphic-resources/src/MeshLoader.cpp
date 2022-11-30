#include <module/resource/MeshLoader.hpp>

#include <Module/ModuleManager.hpp>
#include <module/logger/OneLogger.hpp>

#include <filesystem>

of::module::EngineResourceType of::module::interface::IEngineResource<of::module::mesh::Loader>::type = of::module::EngineResourceType::MeshLoader;

namespace of::module::mesh
{

	bool Loader::loadMesh(const common::String& name)
	{
		common::String path = "Data/" + name;
		if (!std::filesystem::exists(path))
		{
			auto& logger = engine::GetModule <logger::OneLogger>().getLogger("mesh::Loader");
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

	std::shared_ptr<swizzle::asset2::IMeshAsset> Loader::requestMesh(const common::String& name, const common::String& path)
	{
		if (!name.empty())
		{
			std::unordered_map<common::String, std::shared_ptr<swizzle::asset2::IMeshAsset>>::iterator it;
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

	void Loader::requestRemovalOfMesh(const common::String& name)
	{
		if (loadedMeshes.find(name) != loadedMeshes.end())
		{
			auto& logger = engine::GetModule <logger::OneLogger>().getLogger("mesh::Loader");
			logger.Info("Unloading mesh " + name, logger.fileInfo(__FILE__, __LINE__));
			loadedMeshes.erase(name);
		}
	}

}
#include <module/resource/MeshLoader.hpp>

#include <module/logger/OneLogger.hpp>
#include <module/window/GraphicsProxy.hpp>

#include <filesystem>

of::module::EngineResourceType of::module::interface::IEngineResource<of::module::mesh::Loader>::type = of::module::EngineResourceType::MeshLoader;

namespace of::module::mesh
{

	bool Loader::loadMesh(std::shared_ptr<swizzle::asset2::IMeshAsset>& outMeshAsset, const common::String& name, swizzle::asset2::MeshAssetLoaderDescription desc)
	{
		common::String path = "Data/" + name;
		if (!std::filesystem::exists(path))
		{
			auto& logger = engine::GetModule <logger::OneLogger>().getLogger("of::resource::mesh::Loader");
			logger.Error("Unable to load mesh [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
			if (name == Settings::meshPath + missingMesh)
			{
				logger.Critical("Unable to load default mesh! - - - Crashing!");
				throw;
			}
			lastResult = false;
			return false;
		}

		outMeshAsset = swizzle::asset2::LoadMesh(path.c_str(), desc);
		lastResult = true;
		return true;
	}

	bool Loader::getResult()
	{
		return lastResult;
	}

	of::resource::Model Loader::requestModel(const common::String& name, const common::String& path, const bool& collisionModel)
	{

		if (!name.empty())
		{
			/*model does not exist in the current loaded one*/
			if (mLoadedModels.find({ path + name , collisionModel}) == mLoadedModels.end())
			{
				auto& wnd = of::engine::GetModule<of::module::window::Proxy>();
				auto gfx = wnd.getGfxDevice();

				std::shared_ptr<swizzle::asset2::IMeshAsset> meshAsset;
				swizzle::asset2::MeshAssetLoaderDescription meshDescription = {};
				meshDescription.mLoadPossitions = {
				{
					swizzle::asset2::AttributeTypes::VertexPosition, 0u},
				};
				if (collisionModel == false)
				{
					meshDescription.mLoadPossitions = {
						{swizzle::asset2::AttributeTypes::VertexPosition, 0u},
						{swizzle::asset2::AttributeTypes::NormalVector, sizeof(float) * 3u},
						{swizzle::asset2::AttributeTypes::UvCoordinates, sizeof(float) * 6u},
						{swizzle::asset2::AttributeTypes::BoneIndices, sizeof(float) * 8u},
						{swizzle::asset2::AttributeTypes::BoneWeights, sizeof(float) * 12u},
					};
				}

				if (loadMesh(meshAsset, path + name, meshDescription) == false)
				{
					// fallback to missing mesh
					of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::resource::mesh::Loader").Error("Unable to load mesh: ", path + name, "file not found!");
					of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::resource::mesh::Loader").Info("Fallback to default mesh to use for model");
					return requestModel(missingMesh, Settings::meshPath, collisionModel);
				}

				auto& model = mLoadedModels[{path + name, collisionModel}];
				model.mesh = meshAsset;
				if (meshAsset->hasAnimations() && collisionModel == false)
				{
					model.mBoneBuffer = gfx->createBuffer(swizzle::gfx::GfxBufferType::UniformBuffer, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
					model.mBoneBuffer->setBufferData((U8*)meshAsset->getAnimationDataPtr(0, 0), meshAsset->getNumberOfBones() * sizeof(glm::mat4),
						sizeof(glm::mat4));
				}

				model.mMeshBuffer = gfx->createBuffer(swizzle::gfx::GfxBufferType::Vertex, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
				if(collisionModel)
					model.mMeshBuffer->setBufferData((U8*)meshAsset->getVertexDataPtr(), meshAsset->getVertexDataSize(), sizeof(float) * 3u);
				else if (name.ends_with(".obj"))
				{
					model.mMeshBuffer->setBufferData((U8*)meshAsset->getVertexDataPtr(), meshAsset->getVertexDataSize(), sizeof(float) * (3 + 3 + 2));
				}
				else
					model.mMeshBuffer->setBufferData((U8*)meshAsset->getVertexDataPtr(), meshAsset->getVertexDataSize(), sizeof(float) * 16u);

				model.mIndexBuffer = gfx->createBuffer(swizzle::gfx::GfxBufferType::Index, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
				model.mIndexBuffer->setBufferData((U8*)meshAsset->getIndexDataPtr(), meshAsset->getIndexDataSize(),
					sizeof(U32) * 3u);
				model.mValid = true;
				return model;
			}
			return mLoadedModels[{path + name, collisionModel}];

		}
		of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::resource::mesh::Loader").Error("Unable to load mesh: ", path + name, " name is invalid!");
		of::engine::GetModule<of::module::logger::OneLogger>().getLogger("of::resource::mesh::Loader").Info("Fallback to default mesh to use for model");
		return requestModel(missingMesh, Settings::meshPath, collisionModel);
	}

	void Loader::requestRemovalOfModel(const common::String& name, const common::String& path, const bool& collisionModel)
	{
		if (mLoadedModels.find({ path + name , collisionModel }) != mLoadedModels.end())
		{
			auto& logger = engine::GetModule <logger::OneLogger>().getLogger("of::resource::mesh::Loader");
			logger.Info("Unloading model " + path + name, logger.fileInfo(__FILE__, __LINE__));
			mLoadedModels.erase({ path + name, collisionModel });
		}
	}

}
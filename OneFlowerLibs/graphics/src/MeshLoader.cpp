#include <module/resource/MeshLoader.hpp>
#include <module/resource/internalLoaders.hpp>

#include <logger/Logger.hpp>

#include <filesystem>

static of::module::mesh::Loader* g_meshLoader = nullptr;

namespace of::module::mesh
{

	Loader::Loader(std::weak_ptr<swizzle::gfx::GfxDevice> gfx) : mGfxDev(gfx)
	{
	}

	std::shared_ptr<of::gfx::Mesh> Loader::loadMesh(const common::String& name, const bool isCollisionModel, swizzle::asset2::MeshAssetLoaderDescription desc)
	{
		std::shared_ptr<of::gfx::Mesh> mesh = std::make_shared<of::gfx::Mesh>();
		common::String path = "Data/" + name;
		if (!std::filesystem::exists(path))
		{
			auto& logger = of::logger::get().getLogger("of::resource::mesh::Loader");
			logger.Error("Unable to load mesh [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
			if (name == engine::path::meshes + missingMesh)
			{
				logger.Critical("Unable to load default mesh! - - - Crashing!");
				throw;
			}
			lastResult = false;
			return nullptr;
		}

		auto gfx = mGfxDev.lock();
		if (gfx.operator bool() == false)
		{
			logger::get().getLogger("of::resource::mesh::Loader").Error("Gfx device no longer valid! Unable to request mesh!");
			return nullptr;
		}


		mesh->meshAsset = swizzle::asset2::LoadMesh(path.c_str(), desc);
		auto meshAsset = mesh->meshAsset;

		if (mesh->meshAsset->hasAnimations() && isCollisionModel == false)
		{
			mesh->mBoneBuffer = gfx->createBuffer(swizzle::gfx::GfxBufferType::UniformBuffer, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
			mesh->mBoneBuffer->setBufferData((U8*)meshAsset->getAnimationDataPtr(0, 0), meshAsset->getNumberOfBones() * sizeof(glm::mat4),
				sizeof(glm::mat4));
		}

		mesh->mMeshBuffer = gfx->createBuffer(swizzle::gfx::GfxBufferType::Vertex, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
		if (isCollisionModel)
		{
			mesh->mMeshBuffer->setBufferData((U8*)meshAsset->getVertexDataPtr(), meshAsset->getVertexDataSize(), sizeof(float) * 3u);
		}
		else if (name.ends_with(".obj"))
		{
			mesh->mMeshBuffer->setBufferData((U8*)meshAsset->getVertexDataPtr(), meshAsset->getVertexDataSize(), sizeof(float) * 8u);
		}
		else
		{
			mesh->mMeshBuffer->setBufferData((U8*)meshAsset->getVertexDataPtr(), meshAsset->getVertexDataSize(), sizeof(float) * 16u);
		}

		if (meshAsset->hasIndexData())
		{
			mesh->mIndexBuffer = gfx->createBuffer(swizzle::gfx::GfxBufferType::Index, swizzle::gfx::GfxMemoryArea::DeviceLocalHostVisible);
			mesh->mIndexBuffer->setBufferData((U8*)meshAsset->getIndexDataPtr(), meshAsset->getIndexDataSize(),
				sizeof(U32) * 3u);
		}

		lastResult = true;
		mLoadedModels[{path + name, isCollisionModel}] = mesh;
		
		return mesh;
	}

	bool Loader::getResult()
	{
		return lastResult;
	}

	std::shared_ptr<of::gfx::Mesh> Loader::requestModel(const common::String& name, const common::String& path, const bool collisionModel)
	{
		auto& logger = of::logger::get().getLogger("mesh::Loader");
		logger.Info("Request texture [" + name + "]", logger.fileInfo(__FILE__, __LINE__));
		if (!name.empty())
		{

			auto& it = mLoadedModels[{path + name, collisionModel}];
			
			if (it.expired())
			{
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
				auto model = loadMesh(path + name, collisionModel, meshDescription);
				if (model.operator bool())
				{
					return model;
				}
				else
				{
					logger.Warning("Request mesh [" + name + "] failed, using fallback", logger.fileInfo(__FILE__, __LINE__));
					model = loadMesh(path + missingMesh, collisionModel, meshDescription);
					if (model.operator bool())
					{
						return model;
					}
					else
					{
						logger.Critical("Fallback mesh loading failed, exiting!", logger.fileInfo(__FILE__, __LINE__));
						// Todo: use engine::exit(), which forces a shutdown, with error dialog.
						std::exit(-1);
					}
				}
			}
			else
			{
				return it.lock();
			}
		}
		
		// name is missing, just crash...

		of::logger::get().getLogger("of::resource::mesh::Loader").Error("Unable to load mesh: ", path + name, " name is invalid!");
		of::logger::get().getLogger("of::resource::mesh::Loader").Info("Fallback to default mesh to use for model");
		return nullptr;
	}

	void Loader::requestRemovalOfModel(const common::String& name, const common::String& path, const bool collisionModel)
	{
		if (mLoadedModels.find({ path + name , collisionModel }) != mLoadedModels.end())
		{
			auto& logger = of::logger::get().getLogger("of::resource::mesh::Loader");
			logger.Info("Unloading model " + path + name, logger.fileInfo(__FILE__, __LINE__));
			mLoadedModels.erase({ path + name, collisionModel });
		}
	}

	Loader& get()
	{
		return *g_meshLoader;
	}

	void init(std::weak_ptr<swizzle::gfx::GfxDevice> gfxDevice)
	{
		if (g_meshLoader == nullptr)
		{
			g_meshLoader = new Loader(gfxDevice);
		}
	}

	void shutdown()
	{
		delete g_meshLoader;
		g_meshLoader = nullptr;
	}
}
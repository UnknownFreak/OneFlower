#include <internal/editorContext.hpp>

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>

#include <engine/paths.hpp>

#include <asset/assetIndex.hpp>

#include <asset/asset.hpp>
#include <asset/internalAsset.hpp>

static of::editor::EditorContext* s_editorContext = nullptr;

namespace of::editor
{

	void EditorContext::buildModOrderFile(const of::common::String& modFile, std::set<of::common::String>& dependencies)
	{
		auto& manager = asset::get();
		for (auto& name : dependencies)
		{
			manager.loadOrder.emplace_back(name);
		}
		manager.loadOrder.emplace_back(modFile);
		auto& logger = of::logger::get().getLogger("File::Asset::Manager");
		logger.Info("New load order built: Order is as follows,");
		for (auto& order : manager.loadOrder)
		{
			logger.Info(order);
		}
		logger.Info("End of load order.");
	}

	void EditorContext::saveGameDatabase(const of::common::String& filename)
	{
		header.name = filename;
		of::common::String indexName = filename + ".index";
		auto& archive = asset::getAssetRequestor();
		std::ofstream file(of::engine::path::data / filename, std::ios::binary | std::ios::out);
		std::ofstream index(of::engine::path::data / indexName, std::ios::binary | std::ios::out);
		{

			of::asset::AssetIndex ind;
			cereal::BinaryOutputArchive mainAr(file);
			cereal::BinaryOutputArchive indexAr(index);
			ind.flags = asset::ObjectFlag::NoFlag;
			ind.ID = of::common::uuid::nil();
			ind.type = asset::ObjectType::Header;
			ind.modFile = header.name;
			ind.row = file.tellp();
			indexAr(ind);
			mainAr(header);

			//lang.save(ind, file, indexAr, mainAr);
			archive.save(ind, file, indexAr, mainAr, header);

			ind.ID = of::common::uuid::nil();
			ind.type = asset::ObjectType::EoF;
			ind.row = file.tellp();
			ind.flags = asset::ObjectFlag::EoF;
			indexAr(ind);
		}
		file.close();
		index.close();
	}

	void EditorContext::loadAllEditorVariables()
	{
		auto& manager = asset::get();
		manager.requestor.editorLoadAll();
	}

	void initEditorContext()
	{
		if (s_editorContext == nullptr)
		{
			s_editorContext = new EditorContext();
		}
	}

	void shutdownEditorContext()
	{
		if (s_editorContext)
		{
			delete s_editorContext;
			s_editorContext = nullptr;
		}
	}

	EditorContext& getEditorContext()
	{
		return *s_editorContext;
	}
}
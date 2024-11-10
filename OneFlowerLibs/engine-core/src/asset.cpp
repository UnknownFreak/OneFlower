#include <asset/asset.hpp>
#include <asset/internalAsset.hpp>

#include <engine/paths.hpp>
#include <fstream>

#include <cereal/archives/xml.hpp>
#include <cereal/types/vector.hpp>

#include <asset/loadHeader.hpp>

static of::asset::AssetManager* g_assetManager = nullptr;

namespace of::asset
{

	AssetManager::AssetManager() : loadOrder(), requestor(of::engine::path::data, loadOrder)
	{
	}

	void init()
	{
		if (g_assetManager == nullptr)
		{
			g_assetManager = new AssetManager();
		}
	}

	void shutdown()
	{
		if (g_assetManager)
		{
			delete g_assetManager;
			g_assetManager = nullptr;
		}
	}

	// use for internal modules...
	AssetManager& get()
	{
		return *g_assetManager;
	}


	static void defaults()
	{
		g_assetManager->loadOrder.clear();
		const of::common::String defaultFile = "of.main";
		g_assetManager->loadOrder.emplace_back(defaultFile);
		of::asset::Header h;
		if (of::asset::loadHeader(defaultFile, h) == false)
		{
			// even default failed to load... exiting
			std::exit(-1);
		}
	}

	static void validateFileHeaders()
	{
		// could be optimized, but this is done once every startup... no need to be efficient.
		std::vector<of::common::String> valid;
		for (auto& file : g_assetManager->loadOrder)
		{
			of::asset::Header h;
			if (of::asset::loadHeader(file, h) == false)
			{
				of::logger::get().Error("Asset header failed to validate - removing");
			}
			else
			{
				valid.emplace_back(file);
			}
		}
		g_assetManager->loadOrder = valid;
		if (valid.empty())
		{
			defaults();
		}
	}
	static void clearDuplicates()
	{
		auto& vec = g_assetManager->loadOrder;
		// clear duplicates by adding all elements to a set, then converting the set back to a vector...
		// again, done once every startup... no need to be efficient...
		std::set<of::common::String> s(vec.begin(), vec.end());
		g_assetManager->loadOrder = std::vector<of::common::String>(s.begin(), s.end());
	}

	void setLoadOrder(const std::filesystem::path& loadOrderFile)
	{
		if (g_assetManager == nullptr)
		{
			of::logger::get().Critical("Asset subsystsem not initialized before setLoadOrder... exiting...");
			// todo replace with engine::exit(error code)
			std::exit(-1);
		}
		std::ifstream file(loadOrderFile, std::ios::in);
		if(file.is_open())
		{
			try
			{
				// no idea why rapidxml bloats the stack like this...
				cereal::XMLInputArchive xmlLoader(file);
				xmlLoader(g_assetManager->loadOrder);
			}
			catch (cereal::Exception e)
			{
				of::logger::get().Error("Unable to set load order!");
				of::logger::get().Error(e.what());
				// 
				defaults();
			}
			validateFileHeaders();
		}
		else
		{
			defaults();
		}
		clearDuplicates();
	}

	of::asset::Requestor& getAssetRequestor()
	{
		return g_assetManager->requestor;
	}

};
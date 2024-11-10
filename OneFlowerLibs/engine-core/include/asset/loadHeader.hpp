#pragma once

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>

#include <asset/assetIndex.hpp>
#include <engine/paths.hpp>

#include <logger/Logger.hpp>

namespace of::asset
{
	template< typename T>
	bool loadHeader(common::String modName, T& myheader)
	{
		bool eof = false;
		asset::AssetIndex ind;
		of::common::String indexName = modName + ".index";
		std::ifstream index(of::engine::path::data / indexName, std::ios::binary);
		std::ifstream database(of::engine::path::data / modName, std::ios::binary);
		auto& logger = of::logger::get().getLogger("file::archive::loadHeader");
		if (!index.is_open())
			logger.Critical("Unable to open mod index file [" + indexName + "]", logger.fileInfo(__FILE__, __LINE__));
		else if (!database.is_open())
			logger.Critical("Unable to open database file [" + modName + "]", logger.fileInfo(__FILE__, __LINE__));
		else
		{
			cereal::BinaryInputArchive ar(index);
			{
				while (!eof)
				{
					ar(ind);
					if (ind.type == asset::ObjectType::Header)
					{
						database.seekg(ind.row);
						cereal::BinaryInputArchive headerLoad(database);
						headerLoad(myheader);
						index.close();
						database.close();
						return myheader.isValid();
					}
					else if (ind.flags == asset::ObjectFlag::EoF)
						eof = true;
				}
			}
		}
		logger.Critical("Unable to load mod header for mod [" + modName + "]", logger.fileInfo(__FILE__, __LINE__));
		return false;
	}
}
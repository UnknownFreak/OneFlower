#pragma once

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>

#include <utils/common/string.hpp>

#include <file/archive/EntityIndex.hpp>

#include <module/ModuleManager.hpp>
#include <module/logger/OneLogger.hpp>

namespace of::file::archive
{
	template< typename T>
	bool loadHeader(common::String modName, T& myheader)
	{
		bool eof = false;
		file::archive::EntityIndex ind;
		std::ifstream index("Data//" + modName + ".index", std::ios::binary);
		std::ifstream database("Data//" + modName, std::ios::binary);
		auto& logger = of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("file::archive::loadHeader");
		if (!index.is_open())
			logger.Critical("Unable to open mod index file [" + modName + ".index]", logger.fileInfo(__FILE__, __LINE__));
		else if (!database.is_open())
			logger.Critical("Unable to open database file [" + modName + "]", logger.fileInfo(__FILE__, __LINE__));
		else
		{
			cereal::BinaryInputArchive ar(index);
			{
				while (!eof)
				{
					ar(ind);
					if (ind.type == file::ObjectType::Header)
					{
						database.seekg(ind.row);
						cereal::BinaryInputArchive headerLoad(database);
						headerLoad(myheader);
						index.close();
						database.close();
						return true;
					}
					else if (ind.flags == file::ObjectFlag::EoF)
						eof = true;
				}
			}
		}
		logger.Critical("Unable to load mod header for mod [" + modName + "]", logger.fileInfo(__FILE__, __LINE__));
		return false;
	}
}
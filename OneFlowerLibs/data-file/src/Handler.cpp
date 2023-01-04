#include <file/Handler.hpp>
#include <module/logger/OneLogger.hpp>


of::module::EngineResourceType of::module::interface::IEngineResource<of::file::Handler>::type = of::module::EngineResourceType::FileHandler;

namespace of::file
{
	Handler::Handler()
	{
		openedFile.name = "<Not Set>";
	}

	void Handler::buildModOrderFile(const of::common::String& modFile, std::set<of::common::String>& dependencies)
	{
		auto& modLoader = engine::GetModule<Loader>();
		modLoader.loadOrder.clear();
		for (auto& name : dependencies)
		{
			modLoader.loadOrder.insert(std::make_pair(name, modLoader.loadOrder.size()));
		}
		modLoader.loadOrder.insert(std::make_pair(modFile, modLoader.loadOrder.size()));
		auto& logger = of::engine::GetModule<of::module::logger::OneLogger>().getLogger("File::Asset::Manager");
		logger.Info("New load order built: Order is as follows,");
		for (auto& order : modLoader.loadOrder)
		{
			logger.Info(order.first);
		}
		logger.Info("End of load order.");
	}

	void Handler::saveGameDatabase(std::string filename, Header& modhdr)
	{
		std::ofstream file(of::common::dataPath + filename, std::ios::binary | std::ios::out);
		filename.append(".index");
		std::ofstream index(of::common::dataPath + filename, std::ios::binary | std::ios::out);
		{

			archive::EntityIndex ind;
			cereal::BinaryOutputArchive mainAr(file);
			cereal::BinaryOutputArchive indexAr(index);
			ind.flags = ObjectFlag::NoFlag;
			ind.ID = of::common::uuid::nil();
			ind.type = ObjectType::Header;
			ind.modFile = modhdr.name;
			ind.row = file.tellp();
			indexAr(ind);
			mainAr(modhdr);

			//lang.save(ind, file, indexAr, mainAr);
			archive.save(ind, file, indexAr, mainAr, modhdr);

			ind.ID = of::common::uuid::nil();
			ind.type = ObjectType::EoF;
			ind.row = file.tellp();
			ind.flags = ObjectFlag::EoF;
			indexAr(ind);
		}
		file.close();
		index.close();
	}

	void Handler::loadAllEditorVariables()
	{
		archive.editorLoadAll();
	}

	file::Loader& Handler::getLoader()
	{
		return of::engine::GetModule<file::Loader>();
	}

	of::module::EngineResourceType& Handler::getType() const
	{
		return type;
	}
}
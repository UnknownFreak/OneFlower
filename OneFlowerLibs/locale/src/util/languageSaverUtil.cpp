#include <locale/LanguageRequestor.hpp>

#include <file/archive/loadHeader.hpp>

#include "langaugeSaverUtil.hpp"


namespace of::locale::utils
{
	std::map<common::String, TranslationStringContainer> loadLanguages(const std::vector<common::String>& languageFiles)
	{
		std::map<common::String, TranslationStringContainer> tmp;

		TranslationStringContainer translationStr;
		for (common::String var : languageFiles)
		{
			file::archive::loadHeader("Lang//" + var, translationStr);
			tmp.emplace(var, translationStr);
		}
		return tmp;
	}
	void saveLanguages(const LanguageRequestor& languageRequestor)
	{
		for (auto& x : languageRequestor.languages)
			saveLanguageFile(x.first, (TranslationStringContainer&)x.second);
	}

	void saveLanguageFile(const common::String& filename, TranslationStringContainer& saveable)
	{
		common::String idx = filename;
		std::ofstream file(common::langPath + filename, std::ios::binary);
		idx.append(".index");
		auto& logger = of::engine::GetModule<of::module::Logger::OneLogger>().getLogger("of::locale::utils::saveLanguageFile");
		logger.Debug("Saving file: " + filename);
		std::ofstream index(common::langPath + idx, std::ios::binary);
		{
			file::archive::EntityIndex ind;
			cereal::BinaryOutputArchive mainAr(file);
			cereal::BinaryOutputArchive indexAr(index);
			ind.flags = file::ObjectFlag::NoFlag;
			ind.ID = common::uuid::nil();
			ind.type = file::ObjectType::Header;
			ind.modFile = "notUsed";
			ind.row = file.tellp();
			indexAr(ind);
			mainAr(saveable);
			saveable.stringList.save(ind, file, indexAr, mainAr, {}, true);

			ind.ID = common::uuid::nil();
			ind.type = file::ObjectType::EoF;
			ind.row = file.tellp();
			ind.flags = file::ObjectFlag::EoF;
			indexAr(ind);
		}
	}
}

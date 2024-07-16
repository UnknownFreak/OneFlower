#include <locale/TranslationStringContainer.hpp>

#include <logger/OneLogger.hpp>

of::common::uuid of::file::archive::Trait<of::locale::TranslationStringContainer>::typeId = of::common::uuid("a36a1fa2-4fa8-4384-a4cf-f8910e03b539");

of::locale::StoredTranslatable of::locale::TranslationStringContainer::empty = of::locale::StoredTranslatable("", "");

namespace of::locale
{
#if defined _EDITOR_ || _UNITTESTS_
	void TranslationString::addString(const Core::String & languageName, const Core::uuid & stringId, const Core::String value, const bool& isPatch)
	{
		if (isPatch)
			header.moddedIds[languageName].push_back(stringId);
		else
			header.addedIds[languageName].push_back(stringId);
		stringList.add(new StoredTranslatable(value, language, languageName, stringId, OneVersion(1, 0, 0)));
	}

#endif

	TranslationStringContainer::TranslationStringContainer() : TranslationStringContainer("", "Arial.ttf")
	{
	}

	TranslationStringContainer::TranslationStringContainer(const common::String& language, common::String fontName) : language(language), fontName(fontName), stringList(common::langPath), Requestable(common::Builtin, common::uuid::nil(), OneVersion(1, 0, 0), file::ObjectType::TranslationString)
	{
		setAvailableLanguageFiles();
	}

	TranslationStringContainer::TranslationStringContainer(const TranslationStringContainer& copy) : Requestable(copy), language(language), fontName(fontName), stringList(copy.stringList), header(copy.header)
	{
		fontName = copy.fontName;
		language = copy.language;
		setAvailableLanguageFiles();
	}

	TranslationStringContainer& TranslationStringContainer::operator=(const TranslationStringContainer& right)
	{
		if (this == &right)
			return *this;

		ID = right.ID;
		fromMod = right.fromMod;
		mode = right.mode;
		objectVersion = right.objectVersion;

		fontName = right.fontName;
		language = right.language;
		header = right.header;
		stringList = right.stringList;
		setAvailableLanguageFiles();

		return *this;
	}

	const common::String & TranslationStringContainer::getFontName() const
	{
		return fontName;
	}

	StoredTranslatable& TranslationStringContainer::getPrimitive(const common::String & languageName, const common::uuid & id)
	{
		auto& logger = of::engine::GetModule<of::logger::OneLogger>().getLogger("locale::TranslationStringContainer");
		logger.Debug("Loading translation string value from database: " + language + ", " + languageName + ", " + id.to_string());
		auto ptr = stringList.request<StoredTranslatable>({ languageName, id });
		if (ptr)
			return *ptr;
		return empty;
	}

	LanguageHeader & TranslationStringContainer::getHeader()
	{
		return header;
	}

	void TranslationStringContainer::setAvailableLanguageFiles()
	{
		stringList.fileLoadOrder = { { language, 0} };
	}
	file::archive::TypeInfo TranslationStringContainer::getTrait() const
	{
		return { file::archive::Trait<TranslationStringContainer>::typeId };
	}
}

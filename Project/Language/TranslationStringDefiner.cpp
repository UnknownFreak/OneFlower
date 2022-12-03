#include "TranslationString.hpp"

#include <utils/common/uuid.hpp>

of::common::uuid of::file::archive::Trait<Language::TranslationString>::typeId = of::common::uuid("a36a1fa2-4fa8-4384-a4cf-f8910e03b539");
PrimitiveSaveable<of::common::String> Language::TranslationString::empty = PrimitiveSaveable<of::common::String>("", "");
namespace Language
{
#if defined _EDITOR_ || _UNITTESTS_
	void TranslationString::addString(const of::common::String & languageName, const of::common::uuid & stringId, const of::common::String value, const bool& isPatch)
	{
		if (isPatch)
			header.moddedIds[languageName].push_back(stringId);
		else
			header.addedIds[languageName].push_back(stringId);
		stringList.add(new PrimitiveSaveable<of::common::String>(value, language, languageName, stringId, OneVersion(1, 0, 0)));
	}

#endif

	TranslationString::TranslationString() : TranslationString("", "Arial.ttf")
	{
	}

	TranslationString::TranslationString(const of::common::String& language, of::common::String fontName) : language(language), fontName(fontName), stringList(of::common::langPath), Requestable(of::common::Builtin, of::common::uuid::nil(), OneVersion(1, 0, 0), of::file::ObjectType::TranslationString)
	{
		setAvailableLanguageFiles();
	}

	TranslationString::TranslationString(const TranslationString & copy) : Requestable(copy), language(language), fontName(fontName), stringList(copy.stringList), header(copy.header)
	{
		fontName = copy.fontName;
		language = copy.language;
		setAvailableLanguageFiles();
	}

	TranslationString & TranslationString::operator=(const TranslationString & right)
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

	const of::common::String & TranslationString::getFontName() const
	{
		return fontName;
	}

	PrimitiveSaveable<of::common::String>& TranslationString::getPrimitive(const of::common::String & languageName, const of::common::uuid & id)
	{
		auto& logger = of::engine::GetModule<of::module::logger::OneLogger>().getLogger("TranslationString");
		logger.Debug("Loading translation string value from database: " + language + ", " + languageName + ", " + id.to_string());
		auto ptr = stringList.request<PrimitiveSaveable<of::common::String>>({ languageName, id });
		if (ptr)
			return *ptr;
		return empty;
	}

	LanguageHeader & TranslationString::getHeader()
	{
		return header;
	}

	void TranslationString::setAvailableLanguageFiles()
	{
		stringList.fileLoadOrder = { { language, 0} };
	}
	of::file::archive::TypeInfo TranslationString::getTrait() const
	{
		return { of::file::archive::Trait<TranslationString>::typeId };
	}
}

#include "TranslationString.hpp"

#include <Helpers/uuid.hpp>

Core::uuid Interfaces::Trait<Language::TranslationString>::typeId = Core::uuid("a36a1fa2-4fa8-4384-a4cf-f8910e03b539");
PrimitiveSaveable<Core::String> Language::TranslationString::empty = PrimitiveSaveable<Core::String>("", "");
namespace Language
{
#if defined _EDITOR_ || _UNITTESTS_
	void TranslationString::addString(const Core::String & languageName, const Core::uuid & stringId, const Core::String value, const bool& isPatch)
	{
		if (isPatch)
			header.moddedIds[languageName].push_back(stringId);
		else
			header.addedIds[languageName].push_back(stringId);
		stringList.add(new PrimitiveSaveable<Core::String>(value, language, languageName, stringId, OneVersion(1, 0, 0)));
	}

#endif

	TranslationString::TranslationString() : TranslationString("", "Arial.ttf")
	{
	}

	TranslationString::TranslationString(const Core::String& language, Core::String fontName) : language(language), fontName(fontName), stringList(Core::langPath), IRequestable(Core::Builtin, Core::uuid::nil(), OneVersion(1, 0, 0), Enums::ObjectType::TranslationString)
	{
		setAvailableLanguageFiles();
	}

	TranslationString::TranslationString(const TranslationString & copy) : IRequestable(copy), language(language), fontName(fontName), stringList(copy.stringList), header(copy.header)
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

	const Core::String & TranslationString::getFontName() const
	{
		return fontName;
	}

	PrimitiveSaveable<Core::String>& TranslationString::getPrimitive(const Core::String & languageName, const Core::uuid & id)
	{
		auto& logger = Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("TranslationString");
		logger.Debug("Loading translation string value from database: " + language + ", " + languageName + ", " + id.to_string());
		auto ptr = stringList.request<PrimitiveSaveable<Core::String>>({ languageName, id });
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
	Interfaces::TypeInfo TranslationString::getTrait() const
	{
		return { Interfaces::Trait<TranslationString>::typeId };
	}
}

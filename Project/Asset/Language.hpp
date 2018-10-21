#ifndef Language_HPP
#define Language_HPP
#include <Asset/IRequestable.hpp>
#include <Asset/Requestor.hpp>
#include <Asset/PrimitiveSaveable.hpp>

#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>

#include <Core/String.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class Language : public IRequestable, public IPatch
{
	Core::String fallbackLanguage;

	Core::String selectedLanguage;

	std::vector<Core::String> availableLanguages;
	std::map<Core::String, size_t> languageFiles;

	sf::Font m_font;
	std::string fontName;
	void loadFont(const Core::String& name);
	Requestor<PrimitiveSaveable<Core::String>> stringList;

public:

	Language();
	Language(Core::String fontName);
	Language(const Language& copy);

	Language& operator=(const Language& right);

	sf::Font& getFont();

	Core::String getString(size_t id);
	sf::Text getText(size_t id, size_t charSize);


	// Inherited via IPatch
	virtual void Patch(const IPatch & other) override;

	template<class Archive>
	void load(Archive& ar)
	{
		ar(cereal::base_class<IRequestable>(this));
		ar(fallbackLanguage);
		ar(selectedLanguage);
		ar(availableLanguages);
		ar(languageFiles);
		ar(fontName);
		if (fontName != "")
			loadFont(fontName);
	}
	template<class Archive>
	void save(Archive& ar) const
	{
		ar(cereal::base_class<IRequestable>(this));
		ar(fallbackLanguage);
		ar(selectedLanguage);
		ar(availableLanguages);
		ar(languageFiles);
		ar(fontName);
	}
};

#endif
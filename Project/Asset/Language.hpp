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

#include "LanguageHeader.hpp"

namespace Language
{

	class TranslationString : public IRequestable
	{
		Core::String language;
		LanguageHeader header;
		Core::String fontName;
	public:

		Requestor<PrimitiveSaveable<Core::String>> stringList;


	#if defined _EDITOR_ || _UNITTESTS_

		void addString(const Core::String& language, const size_t& ID, const Core::String value, const bool& isPatch);

	#endif

		TranslationString();
		TranslationString(const Core::String& language, Core::String fontName);
		TranslationString(const TranslationString& copy);

		TranslationString& operator=(const TranslationString& right);

		const Core::String& getFontName() const;

		PrimitiveSaveable<Core::String>& getPrimitive(const Core::String& language, const size_t& id);
		LanguageHeader& getHeader();
		void setAvailableLanguageFiles();

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(language);
			ar(header);
			ar(fontName);
		}
		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IRequestable>(this));
			ar(language);
			ar(header);
			ar(fontName);
		}
	};
}
#endif
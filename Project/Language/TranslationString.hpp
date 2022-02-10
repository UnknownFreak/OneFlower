#ifndef Language_HPP
#define Language_HPP
#include <Interfaces/IRequestable.hpp>
#include <File/Resource/Requestor.hpp>
#include <Helpers/PrimitiveSaveable.hpp>

#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>

#include <Helpers/String.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "LanguageHeader.hpp"

namespace Language
{

	class TranslationString : public Interfaces::IRequestable
	{
		Core::String language;
		LanguageHeader header;
		Core::String fontName;
	public:

		Requestor<PrimitiveSaveable<Core::String>> stringList;


	#if defined _EDITOR_ || _UNITTESTS_

		void addString(const Core::String& language, const Core::uuid& ID, const Core::String value, const bool& isPatch);

	#endif

		TranslationString();
		TranslationString(const Core::String& language, Core::String fontName);
		TranslationString(const TranslationString& copy);

		TranslationString& operator=(const TranslationString& right);

		const Core::String& getFontName() const;

		PrimitiveSaveable<Core::String>& getPrimitive(const Core::String& language, const Core::uuid& id);
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

		// Inherited via IRequestable
		virtual Interfaces::TypeInfo getTrait() const override;
	};
}
#endif
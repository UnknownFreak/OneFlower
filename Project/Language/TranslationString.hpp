#pragma once
#ifndef Language_HPP
#define Language_HPP

#include <file/archive/Requestable.hpp>
#include <file/archive/Requestor.hpp>

#include <Helpers/PrimitiveSaveable.hpp>

#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>

#include <utils/common/string.hpp>

#include "LanguageHeader.hpp"

namespace Language
{
	class TranslationString : public of::file::archive::Requestable
	{
		of::common::String language;
		LanguageHeader header;
		of::common::String fontName;
		static PrimitiveSaveable<of::common::String> empty;
	public:

		of::file::archive::Requestor stringList;


	#if defined _EDITOR_ || _UNITTESTS_

		void addString(const of::common::String& language, const of::common::uuid& ID, const of::common::String value, const bool& isPatch);

	#endif

		TranslationString();
		TranslationString(const of::common::String& language, of::common::String fontName);
		TranslationString(const TranslationString& copy);

		TranslationString& operator=(const TranslationString& right);

		const of::common::String& getFontName() const;

		PrimitiveSaveable<of::common::String>& getPrimitive(const of::common::String& language, const of::common::uuid& id);
		LanguageHeader& getHeader();
		void setAvailableLanguageFiles();

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Requestable>(this));
			ar(language);
			ar(header);
			ar(fontName);
		}
		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Requestable>(this));
			ar(language);
			ar(header);
			ar(fontName);
		}

		// Inherited via IRequestable
		virtual of::file::archive::TypeInfo getTrait() const override;
	};
}
#endif
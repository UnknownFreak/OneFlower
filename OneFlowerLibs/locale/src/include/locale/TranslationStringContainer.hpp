#pragma once
#ifndef Language_HPP
#define Language_HPP

#include <file/archive/Requestor.hpp>

#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>

#include <utils/common/String.hpp>

#include "LanguageHeader.hpp"
#include "StoredTranslatable.hpp"

namespace of::locale
{
	class TranslationStringContainer : public file::archive::Requestable
	{
		common::String language;
		LanguageHeader header;
		common::String fontName;
		static StoredTranslatable empty;
	public:

		file::archive::Requestor stringList;


	#if defined _EDITOR_ || _UNITTESTS_

		void addString(const common::String& language, const common::uuid& ID, const common::String value, const bool& isPatch);

	#endif

		TranslationStringContainer();
		TranslationStringContainer(const common::String& language, common::String fontName);
		TranslationStringContainer(const TranslationStringContainer& copy);

		TranslationStringContainer& operator=(const TranslationStringContainer& right);

		const common::String& getFontName() const;

		StoredTranslatable& getPrimitive(const common::String& language, const common::uuid& id);
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
		virtual file::archive::TypeInfo getTrait() const override;
	};
}
#endif
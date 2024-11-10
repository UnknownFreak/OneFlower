#pragma once

#include <asset/iAsset.hpp>

#include <cereal/cereal.hpp>

namespace of::locale
{
	class LocaleSettings : public asset::IAsset
	{
	public:
		of::common::String fontName;

		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAsset>(this));
			ar(fontName);
		}
		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAsset>(this));
			ar(fontName);
		}

		virtual asset::TypeInfo getTrait() const override;
	};
}

CEREAL_REGISTER_TYPE(of::locale::LocaleSettings);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::asset::IAsset, of::locale::LocaleSettings);
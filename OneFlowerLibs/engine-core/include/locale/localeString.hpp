#pragma once

#include <asset/iAsset.hpp>

#include <cereal/cereal.hpp>

namespace of::locale
{

	class LocaleString : public asset::IAsset
	{
	public:

		of::common::String value;


		template<class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAsset>(this));
			ar(value);
		}
		template<class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAsset>(this));
			ar(value);
		}

		virtual asset::TypeInfo getTrait() const override;

	};
}

CEREAL_REGISTER_TYPE(of::locale::LocaleString);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::asset::IAsset, of::locale::LocaleString);
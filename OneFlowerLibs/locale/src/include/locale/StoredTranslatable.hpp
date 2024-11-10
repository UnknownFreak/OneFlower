#pragma once

#include <utils/common/string.hpp>
#include <utils/common/uuid.hpp>

#include <asset/iAsset.hpp>


namespace of::locale
{
	class StoredTranslatable : public of::asset::IAsset
	{

	public:

		inline StoredTranslatable() : StoredTranslatable("", "")
		{
		}

		inline StoredTranslatable(common::String value, common::String name) : StoredTranslatable(value, name, "", common::uuid::nil(), OneVersion::EMPTY)
		{
		}

		inline StoredTranslatable(common::String value, common::String name, const common::String fromMod, const common::uuid ID, const OneVersion version) : IAsset(fromMod, ID, version), value(value)
		{
			editorName = name;
		}

		inline StoredTranslatable(const StoredTranslatable& copy) : IAsset(copy), value(copy.value)
		{
		}

		virtual ~StoredTranslatable() = default;

		common::String value;

		common::String getValue() const;

		// Inherited via Requestable
		virtual of::asset::TypeInfo getTrait() const override;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAsset>(this));
			ar(value);
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAsset>(this));
			ar(value);
		}
	};

}


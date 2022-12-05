#pragma once

#include <utils/common/string.hpp>
#include <utils/common/uuid.hpp>

#include <file/archive/Requestable.hpp>


namespace of::locale
{
	class StoredTranslatable : public of::file::archive::Requestable
	{

	public:

		inline StoredTranslatable() : StoredTranslatable("", "")
		{
		}

		inline StoredTranslatable(common::String value, common::String name) : StoredTranslatable(value, name, "", common::uuid::nil(), OneVersion::EMPTY)
		{
		}

		inline StoredTranslatable(common::String value, common::String name, const common::String fromMod, const common::uuid ID, const OneVersion version) : Requestable(fromMod, ID, version), name(name), value(value)
		{
		}

		inline StoredTranslatable(const StoredTranslatable& copy) : Requestable(copy), name(copy.name), value(copy.value)
		{
		}

		common::String name;
		common::String value;

		common::String getName() const override;
		common::String getValue() const override;

		// Inherited via Requestable
		virtual of::file::archive::TypeInfo getTrait() const override;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<Requestable>(this));
			ar(name);
			ar(value);
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<Requestable>(this));
			ar(name);
			ar(value);
		}
	};

}


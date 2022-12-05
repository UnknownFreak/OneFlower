#pragma once

#include <utils/common/string.hpp>
#include <utils/common/uuid.hpp>

namespace of::locale
{
	class Translatable
	{
		void load();

	public:

		Translatable();

		common::String value;
		common::uuid translationId;

		void reloadIfNeeded();

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(translationId);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(translationId);
			load();
		}
	};

}
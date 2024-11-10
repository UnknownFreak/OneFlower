#pragma once

#include <utils/common/string.hpp>
#include <utils/common/uuid.hpp>

namespace of::locale
{

	void setActiveLocale(const of::common::String& newLocale);
	of::common::String getLocaleString(const of::common::uuid& localeId);
}
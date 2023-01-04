#pragma once

#include <utils/common/uuid.hpp>
#include <concepts>

namespace of::utils::concepts
{
	template<class T>
	concept isConstUuid = std::same_as<T, const of::common::uuid>;

	template<typename T>
	concept has_typeId_member = isConstUuid<decltype(T::typeId)>;
}
#pragma once

#include <functional>
#include <utils/common/uuid.hpp>

namespace of::input
{

	template<typename T>
	struct InputFunctionBinder
	{
		of::common::uuid id;
		std::function<void(T)> m_func;

		bool operator< (const InputFunctionBinder& other) const noexcept { return id < other.id; }
	};

	using AxisInputBind = InputFunctionBinder<const float>;
	using RegularInputBind = InputFunctionBinder<void>;

}
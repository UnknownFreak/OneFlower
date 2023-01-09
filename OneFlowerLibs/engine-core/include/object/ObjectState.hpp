#pragma once
#ifndef ObjectState_HPP
#define ObjectState_HPP


namespace of::object
{
	enum class ObjectState
	{
		Active,
		Inactive,
		Toggle,
		NoRecreate,
		Undefined,
	};
}

#endif
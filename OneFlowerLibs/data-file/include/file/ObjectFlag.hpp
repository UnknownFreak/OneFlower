#ifndef ObjectFlag_HPP
#define ObjectFlag_HPP

namespace of::file
{
	enum class ObjectFlag
	{
		EoF,
		Override,
		AddTo,
		RemoveFrom,
		Modify,
		NoFlag,
		Undefined
	};
}
#endif
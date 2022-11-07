#ifndef LIST_DIR_HPP
#define LIST_DIR_HPP

#include <vector>
#include <common/string.hpp>

namespace of::os
{

	std::vector<common::String> listDirectory(const common::String& path, const common::String& ext, const bool& removeExtInReturn);

#ifdef _UNITTESTS_
	void clearDirectory(const common::String& path);
#endif // _UNITTESTS_
}
#endif

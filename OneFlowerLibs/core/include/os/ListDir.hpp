#ifndef LIST_DIR_HPP
#define LIST_DIR_HPP

#include <vector>
#include <core/String.hpp>

namespace OneFlower::os
{

	std::vector<Core::String> listDirectory(const Core::String& path, const Core::String& ext, const bool& removeExtInReturn);

#ifdef _UNITTESTS_
	void clearDirectory(const Core::String& path);
#endif // _UNITTESTS_
}
#endif

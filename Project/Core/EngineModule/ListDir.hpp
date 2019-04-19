#ifndef LIST_DIR_HPP

#include <vector>
#include <Core/String.hpp>

std::vector<Core::String> listDirectory(const Core::String& path, const Core::String& ext, const bool& removeExtInReturn);

#endif

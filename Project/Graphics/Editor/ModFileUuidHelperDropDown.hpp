#ifndef ModFileUuidHelperDropDown_HPP
#define ModFileUuidHelperDropDown_HPP

#include <map>
#include <vector>

#include <file/FileId.hpp>
#include <file/ObjectType.hpp>



namespace Graphics::Editor::Selectors
{

	static std::map<of::file::ObjectType, std::vector<std::pair<of::common::String, of::file::FileId>>> cached;
	std::vector<std::pair<of::common::String, of::file::FileId>> dropDownComboRefresh(const of::file::ObjectType& type, const std::vector<of::file::FileId>& filter);
	of::file::FileId dropDownSelection(const of::common::String& prompt, const of::file::ObjectType& type, const std::vector<of::file::FileId>& filter);

}

#endif
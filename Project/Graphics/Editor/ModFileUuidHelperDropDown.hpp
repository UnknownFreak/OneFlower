#ifndef ModFileUuidHelperDropDown_HPP
#define ModFileUuidHelperDropDown_HPP

#include <map>
#include <vector>

#include <File/Mod/ModFileUUIDHelper.hpp>
#include <Helpers/Enum/ObjectType.hpp>



namespace Graphics::Editor::Selectors
{

	static std::map<Enums::ObjectType, std::vector<std::pair<Core::String, File::Mod::ModFileUUIDHelper>>> cached;
	std::vector<std::pair<Core::String, File::Mod::ModFileUUIDHelper>> dropDownComboRefresh(const Enums::ObjectType& type, const std::vector<File::Mod::ModFileUUIDHelper>& filter);
	File::Mod::ModFileUUIDHelper dropDownSelection(const Core::String& prompt, const Enums::ObjectType& type, const std::vector<File::Mod::ModFileUUIDHelper>& filter);

}

#endif
#ifndef ModFileUuidHelperDropDown_HPP
#define ModFileUuidHelperDropDown_HPP

#include <map>
#include <vector>

#include <asset/assetId.hpp>
#include <asset/ObjectType.hpp>


namespace Graphics::Editor::Selectors
{

	static std::map<of::asset::ObjectType, std::vector<std::pair<of::common::String, of::asset::AssetId>>> cached;
	std::vector<std::pair<of::common::String, of::asset::AssetId>> dropDownComboRefresh(const of::asset::ObjectType& type, const std::vector<of::asset::AssetId>& filter);

	of::asset::AssetId dropDownSelection(const of::common::String& prompt, const of::asset::ObjectType& type, const std::vector<of::asset::AssetId>& filter);

}

#endif
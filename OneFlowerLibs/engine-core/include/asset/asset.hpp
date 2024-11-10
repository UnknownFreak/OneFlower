#pragma once

#include <filesystem>

#include <asset/requestor.hpp>

namespace of::asset
{
	void setLoadOrder(const std::filesystem::path& loadOrderFile);

	of::asset::Requestor& getAssetRequestor();
};

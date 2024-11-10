#pragma once

#include <asset/header.hpp>

#include <asset/requestor.hpp>

namespace of::asset
{

	class AssetManager
	{

	public:

		AssetManager();
		AssetManager& operator=(const AssetManager&) = delete;

		std::vector<of::common::String> loadOrder;
		asset::Requestor requestor;
	};


	void init();
	void shutdown();

	// use for internal modules...
	AssetManager& get();
}
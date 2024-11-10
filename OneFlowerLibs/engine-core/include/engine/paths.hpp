#pragma once

#include <utils/common/string.hpp>
#include <filesystem>

namespace of::engine::path
{
	inline const std::filesystem::path data = "data";
	inline const std::filesystem::path locale = data / "locale";

	// todo replace with filesystem paths...
	inline const of::common::String textures = "textures/";
	inline const of::common::String skybox = textures + "skybox/";
	inline const of::common::String ui = textures + "ui/";

	inline const of::common::String meshes = "meshes/";
	inline const of::common::String shaders = "shaders/";
}
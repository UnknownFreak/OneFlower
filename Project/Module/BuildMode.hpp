#ifndef BuildMode_HPP
#define BuildMode_HPP

#include <Helpers/String.hpp>
#include <vector>
#include <Helpers/Version.hpp>

namespace Engine
{

	struct BuildMode {

		Core::String toYesNoString(const bool& b) const;

		bool isEditorBuild() const;
		bool isDebugBuild() const;

		OneVersion getBuildNumber() const;
		Core::String getBuildNumberAsStringWithEditor() const;
		Core::String getDetailedBuildInfo() const;

		std::vector<Core::String> toLogString() const;
	};

	BuildMode GetBuildMode();

}

#endif // !BuildMode_HPP

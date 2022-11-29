#ifndef BuildMode_HPP
#define BuildMode_HPP

#include <utils/common/string.hpp>
#include <vector>
#include <utils/common/version.hpp>

namespace Engine
{
	struct BuildMode {

		of::common::String toYesNoString(const bool& b) const;

		bool isEditorMode() const;
		void setEditorMode();
		bool isDebugBuild() const;

		OneVersion getBuildNumber() const;
		of::common::String getBuildNumberAsStringWithEditor() const;
		of::common::String getDetailedBuildInfo() const;

		std::vector<of::common::String> toLogString() const;
		static BuildMode buildMode;

	private:
		bool m_isEditorMode = false;
	};

	BuildMode& GetBuildMode();

}

#endif // !BuildMode_HPP

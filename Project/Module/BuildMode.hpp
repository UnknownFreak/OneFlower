#ifndef BuildMode_HPP
#define BuildMode_HPP

#include <utils/common/String.hpp>
#include <vector>
#include <utils/common/Version.hpp>

namespace of::engine
{
	struct BuildMode {

		common::String toYesNoString(const bool& b) const;

		bool isEditorMode() const;
		void setEditorMode();
		bool isDebugBuild() const;

		OneVersion getBuildNumber() const;
		common::String getBuildNumberAsStringWithEditor() const;
		common::String getDetailedBuildInfo() const;

		std::vector<common::String> toLogString() const;
		static BuildMode buildMode;

	private:
		bool m_isEditorMode = false;
	};

	BuildMode& GetBuildMode();

}

#endif // !BuildMode_HPP

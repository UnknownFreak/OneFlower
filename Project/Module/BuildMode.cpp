#include "BuildMode.hpp"
#include "BuildVersion.hpp"

of::engine::BuildMode of::engine::BuildMode::buildMode;

namespace of::engine
{

	BuildMode& GetBuildMode()
	{
		return of::engine::BuildMode::buildMode;
	}

	common::String BuildMode::toYesNoString(const bool& b) const
	{
		return b ? "Yes" : "No";
	}

	bool BuildMode::isEditorMode() const
	{
#ifdef _EDITOR_
		return true;
#else 
		return m_isEditorMode;
#endif // _EDITOR_

	}
	void BuildMode::setEditorMode()
	{
		m_isEditorMode = true;
	}
	bool BuildMode::isDebugBuild() const
	{
#ifdef _DEBUG
		return true;
#else 
		return false;
#endif // _DEBUG

	}
	OneVersion BuildMode::getBuildNumber() const
	{
		return OneVersion(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REV);
	}

	common::String BuildMode::getBuildNumberAsStringWithEditor() const
	{
		return getBuildNumber().str() + " - Build: " + common::toString(VERSION_BUILD);
	}

	common::String BuildMode::getDetailedBuildInfo() const
	{
		common::String detailedString;
		for (auto s : toLogString())
			detailedString += s + "\n";
		return detailedString;
	}

	std::vector<common::String> BuildMode::toLogString() const
	{
		return { "BuildInfo:", "Version: " + getBuildNumberAsStringWithEditor() , "IsEditorMode: " + toYesNoString(isEditorMode()), "IsDebugBuild: " + toYesNoString(isDebugBuild())};
	}
}

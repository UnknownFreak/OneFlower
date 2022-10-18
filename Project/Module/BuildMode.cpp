#include "BuildMode.hpp"
#include "BuildVersion.hpp"

namespace Engine
{

	BuildMode GetBuildMode()
	{
		return BuildMode();
	}

	Core::String BuildMode::toYesNoString(const bool& b) const
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

	Core::String BuildMode::getBuildNumberAsStringWithEditor() const
	{
		return getBuildNumber().str() + " - Build: " + Core::toString(VERSION_BUILD);
	}

	Core::String BuildMode::getDetailedBuildInfo() const
	{
		Core::String detailedString;
		for (auto s : toLogString())
			detailedString += s + "\n";
		return detailedString;
	}

	std::vector<Core::String> BuildMode::toLogString() const
	{
		return { "BuildInfo:", "Version: " + getBuildNumberAsStringWithEditor() , "IsEditorMode: " + toYesNoString(isEditorMode()), "IsDebugBuild: " + toYesNoString(isDebugBuild())};
	}
}

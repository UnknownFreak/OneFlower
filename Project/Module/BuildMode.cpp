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

	bool BuildMode::isEditorBuild() const
	{
#ifdef _EDITOR_
		return true;
#else 
		return false;
#endif // _EDITOR_

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
		Core::String x = isEditorBuild() ? "E" : "";
		return getBuildNumber().str() + " - Build: " + Core::toString(VERSION_BUILD) + x;
	}

	std::vector<Core::String> BuildMode::toLogString() const
	{
		return { "BuildInfo:", "Version: " + getBuildNumberAsStringWithEditor() , "IsEditorBuild: " + toYesNoString(isEditorBuild()), "IsDebugBuild: " + toYesNoString(isDebugBuild())};
	}
}

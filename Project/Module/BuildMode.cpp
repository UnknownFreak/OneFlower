#include "BuildMode.hpp"
#include "BuildVersion.hpp"

Engine::BuildMode Engine::BuildMode::buildMode;

namespace Engine
{

	BuildMode& GetBuildMode()
	{
		return Engine::BuildMode::buildMode;
	}

	of::common::String BuildMode::toYesNoString(const bool& b) const
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

	of::common::String BuildMode::getBuildNumberAsStringWithEditor() const
	{
		return getBuildNumber().str() + " - Build: " + of::common::toString(VERSION_BUILD);
	}

	of::common::String BuildMode::getDetailedBuildInfo() const
	{
		of::common::String detailedString;
		for (auto s : toLogString())
			detailedString += s + "\n";
		return detailedString;
	}

	std::vector<of::common::String> BuildMode::toLogString() const
	{
		return { "BuildInfo:", "Version: " + getBuildNumberAsStringWithEditor() , "IsEditorMode: " + toYesNoString(isEditorMode()), "IsDebugBuild: " + toYesNoString(isDebugBuild())};
	}
}

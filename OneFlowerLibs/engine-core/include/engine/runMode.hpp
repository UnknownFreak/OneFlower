#pragma once

namespace of::engine
{
	enum class RunMode
	{
		NORMAL,
		EDITOR
	};

	RunMode getRunMode();
	void setRunMode(const RunMode runMode);
	void lockRunMode();
}
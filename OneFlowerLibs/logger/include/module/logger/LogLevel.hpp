#ifndef LogLevel_HPP
#define LogLevel_HPP

#include <core/String.hpp>

namespace OneFlower::Module::Logger
{
	enum class LogLevel
	{
		DBG,
		INFO,
		WARNING,
		ERROR,
		CRITICAL,
		ALWAYS
	};
	inline Core::String to_string(const LogLevel& state, const bool& tabs=true)
	{
		switch (state)
		{
		case LogLevel::DBG: return "DEBUG" + Core::String(tabs ? "\t\t": "");
		case LogLevel::INFO: return "INFO" + Core::String(tabs ? "\t\t" : "");
		case LogLevel::WARNING: return "WARNING" + Core::String(tabs ? "\t\t" : "");
		case LogLevel::ERROR: return "ERROR" + Core::String(tabs ? "\t\t" : "");
		case LogLevel::CRITICAL: return "CRITICAL" + Core::String(tabs ? "\t" : "");
		case LogLevel::ALWAYS: return "INFO" + Core::String(tabs ? "\t\t" : "");
		}
		return "ERR_MISSING_LOG_LEVEL";
	}
	inline LogLevel fromString(const Core::String& string)
	{
		if (string == to_string(LogLevel::DBG, false))
			return LogLevel::DBG;
		else if (string == to_string(LogLevel::INFO, false))
			return LogLevel::INFO;
		else if (string == to_string(LogLevel::WARNING, false))
			return LogLevel::WARNING;
		else if (string == to_string(LogLevel::ERROR, false))
			return LogLevel::ERROR;
		else if (string == to_string(LogLevel::CRITICAL, false))
			return LogLevel::CRITICAL;
		else
			return LogLevel::ALWAYS;
	}
}


#endif
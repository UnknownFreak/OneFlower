#ifndef LogLevel_HPP
#define LogLevel_HPP

#include <utils/common/string.hpp>

namespace of::logger
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
	inline common::String to_string(const LogLevel state, const bool tabs=true)
	{
		switch (state)
		{
		case LogLevel::DBG: return "DEBUG" + common::String(tabs ? "\t\t": "");
		case LogLevel::INFO: return "INFO" + common::String(tabs ? "\t\t" : "");
		case LogLevel::WARNING: return "WARNING" + common::String(tabs ? "\t\t" : "");
		case LogLevel::ERROR: return "ERROR" + common::String(tabs ? "\t\t" : "");
		case LogLevel::CRITICAL: return "CRITICAL" + common::String(tabs ? "\t" : "");
		case LogLevel::ALWAYS: return "INFO" + common::String(tabs ? "\t\t" : "");
		}
		return "ERR_MISSING_LOG_LEVEL";
	}
	inline LogLevel fromString(const common::String& string)
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
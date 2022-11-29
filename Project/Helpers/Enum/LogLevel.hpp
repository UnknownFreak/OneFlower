#ifndef LogLevel_HPP
#define LogLevel_HPP

#include <utils/common/String.hpp>

namespace Enums
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
	inline of::common::String to_string(const Enums::LogLevel& state, const bool& tabs=true)
	{
		switch (state)
		{
		case Enums::LogLevel::DBG: return "DEBUG" + of::common::String(tabs ? "\t\t": "");
		case Enums::LogLevel::INFO: return "INFO" + of::common::String(tabs ? "\t\t" : "");
		case Enums::LogLevel::WARNING: return "WARNING" + of::common::String(tabs ? "\t\t" : "");
		case Enums::LogLevel::ERROR: return "ERROR" + of::common::String(tabs ? "\t\t" : "");
		case Enums::LogLevel::CRITICAL: return "CRITICAL" + of::common::String(tabs ? "\t" : "");
		case Enums::LogLevel::ALWAYS: return "INFO" + of::common::String(tabs ? "\t\t" : "");
		}
		return "ERR_MISSING_LOG_LEVEL";
	}
	inline Enums::LogLevel fromString(const of::common::String& string)
	{
		if (string == to_string(Enums::LogLevel::DBG, false))
			return LogLevel::DBG;
		else if (string == to_string(Enums::LogLevel::INFO, false))
			return LogLevel::INFO;
		else if (string == to_string(Enums::LogLevel::WARNING, false))
			return LogLevel::WARNING;
		else if (string == to_string(Enums::LogLevel::ERROR, false))
			return LogLevel::ERROR;
		else if (string == to_string(Enums::LogLevel::CRITICAL, false))
			return LogLevel::CRITICAL;
		else
			return LogLevel::ALWAYS;
	}
}


#endif
#ifndef LogLevel_HPP
#define LogLevel_HPP

#include <Helpers/String.hpp>

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
	inline Core::String to_string(const Enums::LogLevel& state, const bool& tabs=true)
	{
		switch (state)
		{
		case Enums::LogLevel::DBG: return "DEBUG" + Core::String(tabs ? "\t\t": "");
		case Enums::LogLevel::INFO: return "INFO" + Core::String(tabs ? "\t\t" : "");
		case Enums::LogLevel::WARNING: return "WARNING" + Core::String(tabs ? "\t\t" : "");
		case Enums::LogLevel::ERROR: return "ERROR" + Core::String(tabs ? "\t\t" : "");
		case Enums::LogLevel::CRITICAL: return "CRITICAL" + Core::String(tabs ? "\t" : "");
		case Enums::LogLevel::ALWAYS: return "INFO" + Core::String(tabs ? "\t\t" : "");
		}
		return "ERR_MISSING_LOG_LEVEL";
	}
	inline Enums::LogLevel fromString(const Core::String& string)
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
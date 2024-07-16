#ifndef MODULE_LOGGER_HPP
#define MODULE_LOGGER_HPP

#include "LoggerBase.hpp"
#include <utils/common/string.hpp>
#include <logger/LogLevel.hpp>

namespace of::logger
{
	class ModuleLogger : public LoggerBase
	{
		common::String moduleName;

	public:
		template<class Ty>
		ModuleLogger(const common::String& moduleName, std::shared_ptr<Ty> stream, const LogLevel& level) : LoggerBase(stream, level), moduleName(moduleName)
		{
			this->keyword = "Module: \"" + moduleName + "\" - ";
		};

		ModuleLogger(const ModuleLogger& logger) : ModuleLogger(logger.moduleName, logger.log, logger.level)
		{
		}
		ModuleLogger& operator= (const ModuleLogger& logger) 
		{
			moduleName = logger.moduleName;
			this->log = logger.log;
			this->level = logger.level;
			return *this;
		}

		void setLogLevel(const LogLevel& newLevel) override
		{
			this->Always("Setting new log level for module [" + moduleName +"]: From " + to_string(this->level, false) + " to " + to_string(newLevel, false));
			this->level = newLevel;
		};


	};
}

#endif
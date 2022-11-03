#ifndef MODULE_LOGGER_HPP
#define MODULE_LOGGER_HPP

#include "LoggerBase.hpp"
#include <core\String.hpp>
#include <module\logger\LogLevel.hpp>

namespace OneFlower::Module::Logger
{
	template <class T_Stream>
	class ModuleLogger : public LoggerBase<T_Stream&>
	{
		OneFlower::Core::String moduleName;

	public:
		ModuleLogger(const Core::String& moduleName, T_Stream& stream, const LogLevel& level) : LoggerBase<T_Stream&>(stream, level), moduleName(moduleName)
		{
			this->keyword = "Module: " + moduleName + " ";
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
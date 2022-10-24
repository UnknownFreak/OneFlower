#ifndef MODULE_LOGGER_HPP
#define MODULE_LOGGER_HPP

#include "LoggerBase.hpp"
#include <Helpers\String.hpp>
#include <Helpers\Enum\LogLevel.hpp>

namespace EngineModule
{
	namespace Logger
	{
		template <class T_Stream>
		class ModuleLogger : public LoggerBase<T_Stream&>
		{
			Core::String moduleName;

		public:
			ModuleLogger(const Core::String& moduleName, T_Stream& stream, const Enums::LogLevel& level) : LoggerBase<T_Stream&>(stream, level), moduleName(moduleName)
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

			void setLogLevel(const Enums::LogLevel& newLevel) override
			{
				this->Always("Setting new log level for module [" + moduleName +"]: From " + Enums::to_string(this->level, false) + " to " + Enums::to_string(newLevel, false));
				this->level = newLevel;
			};


		};
	}
}

#endif
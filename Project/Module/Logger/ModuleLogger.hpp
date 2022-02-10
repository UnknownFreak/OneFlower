#ifndef MODULE_LOGGER_HPP
#define MODULE_LOGGER_HPP

#include "LoggerBase.hpp"
#include <Helpers\String.hpp>
#include <Helpers\Enum\LogLevel.hpp>

namespace EngineModule
{
	namespace Logger
	{
		template <class Stream>
		class ModuleLogger : public LoggerBase<Stream&>
		{
			Core::String moduleName;

		public:
			ModuleLogger(const Core::String& moduleName, Stream& stream, const Enums::LogLevel& level) : LoggerBase(stream, level), moduleName(moduleName)
			{
				keyword = "Module: " + moduleName + " ";
			};

			ModuleLogger(const ModuleLogger& logger) : ModuleLogger(logger.moduleName, logger.log, logger.level)
			{
			}
			ModuleLogger& operator= (const ModuleLogger& logger) 
			{
				moduleName = logger.moduleName;
				log = logger.log;
				level = logger.level;
				return *this;
			}

			void setLogLevel(const Enums::LogLevel& newLevel) override
			{
				Always("Setting new log level for module [" + moduleName +"]: From " + Enums::to_string(level, false) + " to " + Enums::to_string(newLevel, false));
				level = newLevel;
			};


		};
	}
}

#endif
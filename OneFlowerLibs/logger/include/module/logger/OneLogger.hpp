#ifndef MAIN_LOGGER_HPP
#define MAIN_LOGGER_HPP

#include "LoggerBase.hpp"

#include "streams/LogSteam.hpp"
#include "streams/BasicLogStream.hpp"
#include "streams/NullStream.hpp"

#include <unordered_map>
#include "ModuleLogger.hpp"

#include <module/ModuleManager.hpp>
#include <module/IEngineModule.hpp>

namespace of::module::logger
{
#ifdef __EDITOR__
		typedef Streams::EditorStream stream

#else
	// TODO change with LogFileStream custom class
	typedef streams::BasicLogStream stream;
#endif

	class OneLogger : public LoggerBase, public interface::IEngineResource<OneLogger>
	{
		static ModuleLogger EMPTY;
		std::unordered_map<common::String, ModuleLogger> moduleLoggers;
	public:
		OneLogger();
		OneLogger(std::shared_ptr<streams::LogStream> logStream);
		~OneLogger();

		ModuleLogger& getLogger(const common::String& moduleName)
		{
			if (this == nullptr)
				return EMPTY;
			if (moduleLoggers.find(moduleName) == moduleLoggers.end())
				moduleLoggers.insert_or_assign(moduleName,
					ModuleLogger(moduleName, log, level));
			return moduleLoggers.at(moduleName);
		}

		template<class logStream>
		ModuleLogger& getLogger(const common::String& moduleName, std::shared_ptr<logStream> customLogger)
		{
			if (this == nullptr)
				return EMPTY;
			if (moduleLoggers.find(moduleName) == moduleLoggers.end())
				moduleLoggers.insert_or_assign(moduleName,
					ModuleLogger(moduleName, customLogger, level));
			return moduleLoggers.at(moduleName);
		}

		EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
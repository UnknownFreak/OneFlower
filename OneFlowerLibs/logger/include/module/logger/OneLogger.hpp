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
	typedef Streams::BasicLogStream stream;
#endif

	class OneLogger : public LoggerBase<stream>, public interface::IEngineResource<OneLogger>
	{
		static Streams::NullStream nullStream;
		static ModuleLogger<Streams::NullStream> EMPTY;
		std::unordered_map<common::String, ModuleLogger<stream>> moduleLoggers;
	public:
		OneLogger();
		~OneLogger();

		ModuleLogger<Streams::LogStream>& getLogger(const common::String& moduleName)
		{
			if (this == nullptr)
				return (ModuleLogger<Streams::LogStream>&)EMPTY;
			if (moduleLoggers.find(moduleName) == moduleLoggers.end())
				moduleLoggers.insert_or_assign(moduleName,
					ModuleLogger<stream>(moduleName, log, level));
			return (ModuleLogger<Streams::LogStream>&)moduleLoggers.at(moduleName);
		}

		EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
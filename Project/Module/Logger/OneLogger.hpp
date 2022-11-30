#ifndef MAIN_LOGGER_HPP
#define MAIN_LOGGER_HPP

#include "LoggerBase.hpp"

#include "LoggerStreams/LogSteam.hpp"
#include "LoggerStreams/BasicLogStream.hpp"
#include "LoggerStreams/NullStream.hpp"

#include <unordered_map>
#include "ModuleLogger.hpp"

#include <module/IEngineModule.hpp>
#include <utils/common/string.hpp>
#include <Helpers\Enum\LogLevel.hpp>

#include <File/GameConfig.hpp>

namespace EngineModule
{
	namespace Logger
	{
#ifdef __EDITOR__
		typedef Streams::EditorStream stream

#else
		// TODO change with LogFileStream custom class
		typedef Streams::BasicLogStream stream;
#endif

		class OneLogger : public LoggerBase<stream>, public of::module::interface::IEngineResource<OneLogger>
		{
			static Streams::NullStream nullStream;
			static ModuleLogger<Streams::NullStream> EMPTY;
			std::unordered_map<of::common::String, ModuleLogger<stream>> moduleLoggers;
		public:
			OneLogger();
			~OneLogger();

			ModuleLogger<Streams::LogStream>& getLogger(const of::common::String& moduleName)
			{
				if (this == nullptr)
					return (ModuleLogger<Streams::LogStream>&)EMPTY;
				if (moduleLoggers.find(moduleName) == moduleLoggers.end())
					moduleLoggers.insert_or_assign(moduleName,
						ModuleLogger<stream>(moduleName, log, level));
				return (ModuleLogger<Streams::LogStream>&)moduleLoggers.at(moduleName);
			}

			of::module::EngineResourceType& getType() const
			{
				return type;
			}
		};
	}
}

#endif
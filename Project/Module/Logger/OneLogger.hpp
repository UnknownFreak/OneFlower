#ifndef MAIN_LOGGER_HPP
#define MAIN_LOGGER_HPP

#include "LoggerBase.hpp"

#include "LoggerStreams/LogSteam.hpp"
#include "LoggerStreams/BasicLogStream.hpp"
#include "LoggerStreams/NullStream.hpp"

#include <unordered_map>
#include "ModuleLogger.hpp"

#include <Interfaces/IEngineModule.hpp>
#include <Helpers\String.hpp>
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

		class OneLogger : public LoggerBase<stream>, public Interfaces::IEngineResource<OneLogger>
		{
			static Streams::NullStream nullStream;
			static ModuleLogger<Streams::NullStream> EMPTY;
			std::unordered_map<Core::String, ModuleLogger<stream>> moduleLoggers;
		public:
			OneLogger();
			~OneLogger();

			ModuleLogger<Streams::LogStream>& getLogger(const Core::String& moduleName)
			{
				if (this == nullptr)
					return (ModuleLogger<Streams::LogStream>&)EMPTY;
				if (moduleLoggers.find(moduleName) == moduleLoggers.end())
					moduleLoggers.insert_or_assign(moduleName,
						ModuleLogger<stream>(moduleName, log, level));
				return (ModuleLogger<Streams::LogStream>&)moduleLoggers.at(moduleName);
			}

			Enums::EngineResourceType& getType() const
			{
				return type;
			}
		};
	}
}

#endif
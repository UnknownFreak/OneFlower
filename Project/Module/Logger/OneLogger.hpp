#ifndef MAIN_LOGGER_HPP
#define MAIN_LOGGER_HPP

#include "LoggerBase.hpp"

#include "LoggerStreams/BasicLogStream.hpp"

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

			std::unordered_map<Core::String, ModuleLogger<stream>> moduleLoggers;
		public:
			OneLogger();
			~OneLogger();

			ModuleLogger<stream>& getLogger(const Core::String& moduleName)
			{
				if (moduleLoggers.find(moduleName) == moduleLoggers.end())
					moduleLoggers.insert_or_assign(moduleName,
						ModuleLogger<stream>(moduleName, log, level));
				return moduleLoggers.at(moduleName);
			}

			Enums::EngineResourceType& getType() const
			{
				return type;
			}
		};
	}
}

#endif
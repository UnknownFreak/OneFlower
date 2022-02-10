#ifndef LogStream_HPP
#define LogStream_HPP

#include <Helpers/String.hpp>
#include <Helpers/Enum/LogLevel.hpp>

namespace EngineModule::Logger::Streams
{
	struct LogStream
	{
		virtual void LogMessage(const Enums::LogLevel& logLevel, const Core::String& message) = 0;
		virtual void flush() = 0;
		virtual void close() = 0;
		virtual ~LogStream() = default;
	};
}

#endif
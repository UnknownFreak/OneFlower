#ifndef LogStream_HPP
#define LogStream_HPP

#include <core/String.hpp>
#include <module/logger/LogLevel.hpp>

namespace OneFlower::Module::Logger::Streams
{
	struct LogStream
	{
		virtual void LogMessage(const LogLevel& logLevel, const Core::String& message) = 0;
		virtual void flush() = 0;
		virtual void close() = 0;
		virtual ~LogStream() = default;
	};
}

#endif
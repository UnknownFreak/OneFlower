#ifndef LogStream_HPP
#define LogStream_HPP

#include <common/string.hpp>
#include <module/logger/LogLevel.hpp>

namespace of::module::Logger::Streams
{
	struct LogStream
	{
		virtual void LogMessage(const LogLevel& logLevel, const common::String& message) = 0;
		virtual void flush() = 0;
		virtual void close() = 0;
		virtual ~LogStream() = default;
	};
}

#endif
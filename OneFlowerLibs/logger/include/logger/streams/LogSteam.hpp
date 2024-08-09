#ifndef LogStream_HPP
#define LogStream_HPP

#include <utils/common/string.hpp>
#include <logger/LogLevel.hpp>

namespace of::logger::streams
{
	struct LogStream
	{
		virtual void LogMessage(const LogLevel logLevel, const common::String& message) = 0;
		virtual void flush() = 0;
		virtual void close() = 0;
		virtual ~LogStream() = default;
	};
}

#endif
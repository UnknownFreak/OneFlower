#pragma once

#include "LogSteam.hpp"

namespace of::module::logger::Streams
{

	class ConsoleLogStream : public LogStream
	{
	public:

		~ConsoleLogStream() = default;
		// Inherited via LogStream
		virtual void LogMessage(const LogLevel& logLevel, const common::String& message) override;
		inline virtual void flush() override {};
		inline virtual void close() override {};
	};
}
#include <logger/streams/ConsoleStream.hpp>

#include <iostream>

namespace of::logger::streams
{

	void ConsoleLogStream::LogMessage(const LogLevel& logLevel, const common::String& message)
	{
		std::cout << of::logger::to_string(logLevel) << " " << message << std::endl;
	}
}


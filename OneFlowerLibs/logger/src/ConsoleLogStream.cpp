#include <module/logger/streams/ConsoleStream.hpp>

#include <iostream>

namespace of::module::logger::Streams
{

	void ConsoleLogStream::LogMessage(const LogLevel& logLevel, const common::String& message)
	{
		std::cout << of::module::logger::to_string(logLevel) << " " << message << std::endl;
	}
}


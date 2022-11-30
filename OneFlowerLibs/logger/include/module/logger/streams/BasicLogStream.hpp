#ifndef BasicLogStream_HPP
#define BasicLogStream_HPP

#include "LogSteam.hpp"
#include <fstream> 

namespace of::module::logger::Streams
{

	class BasicLogStream : public LogStream
	{
		common::String logName;
		std::ofstream log;

	public:

		BasicLogStream(const common::String& fileName);
		BasicLogStream(const BasicLogStream& stream);
		BasicLogStream& operator=(const BasicLogStream& stream);
		~BasicLogStream() = default;
		// Inherited via LogStream
		virtual void LogMessage(const LogLevel& logLevel, const common::String& message) override;
		virtual void flush() override;
		virtual void close() override;
	};
}

#endif
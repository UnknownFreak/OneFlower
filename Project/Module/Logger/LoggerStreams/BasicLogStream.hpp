#ifndef BasicLogStream_HPP
#define BasicLogStream_HPP

#include "LogSteam.hpp"
#include <fstream> 

namespace EngineModule::Logger::Streams
{

	class BasicLogStream : public LogStream
	{
		of::common::String logName;
		std::ofstream log;

	public:

		BasicLogStream(const of::common::String& fileName);
		BasicLogStream(const BasicLogStream& stream);
		BasicLogStream& operator=(const BasicLogStream& stream);
		~BasicLogStream() = default;
		// Inherited via LogStream
		virtual void LogMessage(const Enums::LogLevel& logLevel, const of::common::String& message) override;
		virtual void flush() override;
		virtual void close() override;
	};
}

#endif
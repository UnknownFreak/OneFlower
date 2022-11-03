#ifndef BasicLogStream_HPP
#define BasicLogStream_HPP

#include "LogSteam.hpp"
#include <fstream> 

namespace OneFlower::Module::Logger::Streams
{

	class BasicLogStream : public LogStream
	{
		Core::String logName;
		std::ofstream log;

	public:

		BasicLogStream(const Core::String& fileName);
		BasicLogStream(const BasicLogStream& stream);
		BasicLogStream& operator=(const BasicLogStream& stream);
		~BasicLogStream() = default;
		// Inherited via LogStream
		virtual void LogMessage(const LogLevel& logLevel, const Core::String& message) override;
		virtual void flush() override;
		virtual void close() override;
	};
}

#endif
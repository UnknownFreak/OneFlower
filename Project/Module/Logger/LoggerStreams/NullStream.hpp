#ifndef NullStream_HPP
#define NullStream_HPP

#include "LogSteam.hpp"

namespace EngineModule::Logger::Streams
{

	class NullStream : public LogStream
	{
	public:

		inline virtual void LogMessage(const Enums::LogLevel& , const Core::String& ) override {};
		inline virtual void flush() override {};
		inline virtual void close() override {};
	};
}
#endif
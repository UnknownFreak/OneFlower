#ifndef NullStream_HPP
#define NullStream_HPP

#include "LogSteam.hpp"

namespace OneFlower::Module::Logger::Streams
{
	class NullStream : public LogStream
	{
	public:

		NullStream() = default;
		NullStream(const NullStream& ) {};
		NullStream& operator=(const NullStream& ) { return *this; };
		~NullStream() = default;

		inline virtual void LogMessage(const LogLevel& , const Core::String& ) override {};
		inline virtual void flush() override {};
		inline virtual void close() override {};
	};
}
#endif
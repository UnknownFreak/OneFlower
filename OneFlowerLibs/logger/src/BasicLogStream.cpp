#include <module\logger\streams\BasicLogStream.hpp>

auto iosop = std::ios_base::trunc;

namespace of::module::Logger::Streams
{
	BasicLogStream::BasicLogStream(const common::String& fileName) : log(fileName, iosop), logName(fileName)
	{
		iosop = std::ios_base::app;
	}

	BasicLogStream::BasicLogStream(const BasicLogStream& stream) : BasicLogStream(stream.logName)
	{
	}

	BasicLogStream& BasicLogStream::operator=(const BasicLogStream& stream)
	{
		log.close();
		log.open(stream.logName, iosop);
		logName = stream.logName;
		return *this;
	}

	void BasicLogStream::LogMessage(const LogLevel& logLevel, const common::String& message)
	{
		log << to_string(logLevel) << message << std::endl;
	}

	void BasicLogStream::flush()
	{
		log.flush();
	}

	void BasicLogStream::close()
	{
		log.close();
	}
}
#include <module\logger\streams\BasicLogStream.hpp>

auto iosop = std::ios_base::trunc;

namespace OneFlower::Module::Logger::Streams
{
	BasicLogStream::BasicLogStream(const Core::String& fileName) : log(fileName, iosop), logName(fileName)
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

	void BasicLogStream::LogMessage(const LogLevel& logLevel, const Core::String& message)
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
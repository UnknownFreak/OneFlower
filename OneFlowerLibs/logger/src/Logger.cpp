#include <logger/Logger.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::logger::Logger>::type = of::module::EngineResourceType::Logger;

of::logger::ModuleLogger of::logger::Logger::EMPTY(
	"", std::make_shared<of::logger::streams::NullStream>(), of::logger::LogLevel::ALWAYS);

namespace of::logger
{
	Logger::Logger() : LoggerBase(stream("Log.log"), LogLevel::INFO)
	{
	}

	Logger::Logger(std::shared_ptr<streams::LogStream> logStream) : LoggerBase(logStream, LogLevel::INFO)
	{
	}

	Logger::~Logger()
	{
		log->flush();
		log->close();
	}
}

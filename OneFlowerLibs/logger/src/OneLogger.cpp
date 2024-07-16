#include <logger/OneLogger.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::logger::OneLogger>::type = of::module::EngineResourceType::Logger;

of::logger::ModuleLogger of::logger::OneLogger::EMPTY(
	"", std::make_shared<of::logger::streams::NullStream>(), of::logger::LogLevel::ALWAYS);

namespace of::logger
{
	OneLogger::OneLogger() : LoggerBase(stream("Log.log"), LogLevel::INFO)
	{
	}

	OneLogger::OneLogger(std::shared_ptr<streams::LogStream> logStream) : LoggerBase(logStream, LogLevel::INFO)
	{
	}

	OneLogger::~OneLogger()
	{
		log->flush();
		log->close();
	}
}

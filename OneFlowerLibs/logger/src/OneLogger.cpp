#include <module/logger/OneLogger.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::module::logger::OneLogger>::type = of::module::EngineResourceType::Logger;

of::module::logger::ModuleLogger of::module::logger::OneLogger::EMPTY(
	"", std::make_shared<of::module::logger::Streams::NullStream>(), of::module::logger::LogLevel::ALWAYS);

namespace of::module::logger
{
	OneLogger::OneLogger() : LoggerBase(stream("Log.log"), LogLevel::INFO)
	{
	}

	OneLogger::OneLogger(std::shared_ptr<Streams::LogStream> logStream) : LoggerBase(logStream, LogLevel::INFO)
	{
	}

	OneLogger::~OneLogger()
	{
		log->flush();
		log->close();
	}
}

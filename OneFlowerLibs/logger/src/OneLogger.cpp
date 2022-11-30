#include <module/logger/OneLogger.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::module::logger::OneLogger>::type = of::module::EngineResourceType::Logger;

of::module::logger::Streams::NullStream of::module::logger::OneLogger::nullStream;
of::module::logger::ModuleLogger<of::module::logger::Streams::NullStream> of::module::logger::OneLogger::EMPTY(
	"", of::module::logger::OneLogger::nullStream, of::module::logger::LogLevel::ALWAYS);

namespace of::module::logger
{
	OneLogger::OneLogger() : LoggerBase(stream("Log.log"), LogLevel::INFO)
	{
	}
	OneLogger::~OneLogger()
	{
		log.flush();
		log.close();
	}
}

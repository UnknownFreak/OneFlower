#include <module/logger/OneLogger.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::module::Logger::OneLogger>::type = of::module::EngineResourceType::Logger;

of::module::Logger::Streams::NullStream of::module::Logger::OneLogger::nullStream;
of::module::Logger::ModuleLogger<of::module::Logger::Streams::NullStream> of::module::Logger::OneLogger::EMPTY(
	"", of::module::Logger::OneLogger::nullStream, of::module::Logger::LogLevel::ALWAYS);

namespace of::module::Logger
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

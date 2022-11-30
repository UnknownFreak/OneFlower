#include "OneLogger.hpp"

of::module::EngineResourceType of::module::interface::IEngineResource<EngineModule::Logger::OneLogger>::type = of::module::EngineResourceType::Logger;

EngineModule::Logger::Streams::NullStream EngineModule::Logger::OneLogger::nullStream;
EngineModule::Logger::ModuleLogger<EngineModule::Logger::Streams::NullStream> EngineModule::Logger::OneLogger::EMPTY(
	"", EngineModule::Logger::OneLogger::nullStream, Enums::LogLevel::ALWAYS);

namespace EngineModule
{
	namespace Logger
	{
		OneLogger::OneLogger() : LoggerBase(stream("Log.log"), Enums::LogLevel::INFO)
		{
		}
		OneLogger::~OneLogger()
		{
			log.flush();
			log.close();
		}
	}
}

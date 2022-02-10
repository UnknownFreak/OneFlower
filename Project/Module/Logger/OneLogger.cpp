#include "OneLogger.hpp"

Enums::EngineResourceType Interfaces::IEngineResource<EngineModule::Logger::OneLogger>::type = Enums::EngineResourceType::Logger;


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

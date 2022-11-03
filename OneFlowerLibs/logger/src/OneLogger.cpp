#include <module/logger/OneLogger.hpp>

OneFlower::Module::EngineResourceType OneFlower::Module::Interface::IEngineResource<OneFlower::Module::Logger::OneLogger>::type = OneFlower::Module::EngineResourceType::Logger;

OneFlower::Module::Logger::Streams::NullStream OneFlower::Module::Logger::OneLogger::nullStream;
OneFlower::Module::Logger::ModuleLogger<OneFlower::Module::Logger::Streams::NullStream> OneFlower::Module::Logger::OneLogger::EMPTY(
	"", OneFlower::Module::Logger::OneLogger::nullStream, OneFlower::Module::Logger::LogLevel::ALWAYS);

namespace OneFlower::Module::Logger
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

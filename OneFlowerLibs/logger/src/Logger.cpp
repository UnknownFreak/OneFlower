#include <logger/Logger.hpp>

of::logger::ModuleLogger of::logger::Logger::EMPTY(
	"", std::make_shared<of::logger::streams::NullStream>(), of::logger::LogLevel::ALWAYS);

of::logger::Logger* g_logger = nullptr;

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

	void init()
	{
		if (g_logger == nullptr)
		{
			g_logger = new Logger();
		}
	}

	void shutdown()
	{
		delete g_logger;
		g_logger = nullptr;
	}

	Logger& get()
	{
		return *g_logger;
	}
}

#include "Logger.hpp"

Logger* Logger::logger;
Logger::Logger() : log("Log.log")
{
}

Logger& Logger::getLogger()
{
	if (!logger)
		logger = new Logger();
	return *logger;
}

void Logger::free()
{
	delete logger;
}

void Logger::Debug(Core::String message, Core::String filename, size_t line)
{
	getLogger().log << "[DEBUG] " << message << ": " << filename << " (" << line << ")" << std::endl;
}

void Logger::Info(Core::String message, Core::String filename, size_t line)
{
	getLogger().log << "[INFO] " << message << ": " << filename << " (" << line << ")" << std::endl;
}

void Logger::Fine(Core::String message, Core::String filename, size_t line)
{
	getLogger().log << "[FINE] " << message << ": " << filename << " (" << line << ")" << std::endl;
}

void Logger::Warning(Core::String message, Core::String filename, size_t line)
{
	getLogger().log << "[WARNING] " << message << ": " << filename << " (" << line << ")" << std::endl;
}

void Logger::Error(Core::String message, Core::String filename, size_t line)
{
	getLogger().log << "[ERROR] " << message << ": " << filename << " (" << line << ")" << std::endl;
}

void Logger::Severe(Core::String message, Core::String filename, size_t line)
{
	getLogger().log << "[SEVERE] " << message << ": " << filename << " (" << line << ")" << std::endl;
}

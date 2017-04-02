#include "Logger.hpp"

#ifdef _EDITOR_
#include <EditorManager\EditorCore.hpp>
#endif

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

void Logger::initialize()
{
	getLogger();
}

void Logger::Debug(Core::String message, Core::String filename, size_t line)
{
	Logger::Debug(message + " - " + filename + " (" + std::to_string(line) + ")");
}

void Logger::Info(Core::String message, Core::String filename, size_t line)
{
	Logger::Info(message + " - " + filename + " (" + std::to_string(line) + ")");
}

void Logger::Fine(Core::String message, Core::String filename, size_t line)
{
	Logger::Fine(message + " - " + filename + " (" + std::to_string(line) + ")");
}

void Logger::Warning(Core::String message, Core::String filename, size_t line)
{
	Logger::Warning(message + " - " + filename + " (" + std::to_string(line) + ")");
}

void Logger::Error(Core::String message, Core::String filename, size_t line)
{
	Logger::Error(message + " - " + filename + " (" + std::to_string(line) + ")");
}

void Logger::Severe(Core::String message, Core::String filename, size_t line)
{
	Logger::Severe(message + " - " + filename + " (" + std::to_string(line) + ")");
}

void Logger::Debug(Core::String message)
{
	getLogger().log << "[DEBUG]\t\t" << message << std::endl;
#ifdef _EDITOR_
	auto logmsg = gcnew EditorResources::Message::Message();
	logmsg->message = gcnew String(message.c_str());
	logmsg->type = EditorResources::Message::Message::MsgType::Debug;
	auto msgargs = gcnew EditorResources::Functionality::EditorLogEventArgs();
	msgargs->logMessage = logmsg;
	EditorResources::Functionality::EditorEvents::OnLogEvent(msgargs);
#endif
}

void Logger::Info(Core::String message)
{
	getLogger().log << "[INFO]\t\t" << message << std::endl;
#ifdef _EDITOR_
	auto logmsg = gcnew EditorResources::Message::Message();
	logmsg->message = gcnew String(message.c_str());
	logmsg->type = EditorResources::Message::Message::MsgType::Info;
	auto msgargs = gcnew EditorResources::Functionality::EditorLogEventArgs();
	msgargs->logMessage = logmsg;
	EditorResources::Functionality::EditorEvents::OnLogEvent(msgargs);
#endif
}

void Logger::Fine(Core::String message)
{
	getLogger().log << "[FINE]\t\t" << message << std::endl;
#ifdef _EDITOR_
	auto logmsg = gcnew EditorResources::Message::Message();
	logmsg->message = gcnew String(message.c_str());
	logmsg->type = EditorResources::Message::Message::MsgType::Fine;
	auto msgargs = gcnew EditorResources::Functionality::EditorLogEventArgs();
	msgargs->logMessage = logmsg;
	EditorResources::Functionality::EditorEvents::OnLogEvent(msgargs);
#endif
}

void Logger::Warning(Core::String message)
{
	getLogger().log << "[WARNING]\t" << message << std::endl;
#ifdef _EDITOR_
	auto logmsg = gcnew EditorResources::Message::Message();
	logmsg->message = gcnew String(message.c_str());
	logmsg->type = EditorResources::Message::Message::MsgType::Warning;
	auto msgargs = gcnew EditorResources::Functionality::EditorLogEventArgs();
	msgargs->logMessage = logmsg;
	EditorResources::Functionality::EditorEvents::OnLogEvent(msgargs);
#endif
}

void Logger::Error(Core::String message)
{
	getLogger().log << "[ERROR]\t\t" << message << std::endl;
#ifdef _EDITOR_
	auto logmsg = gcnew EditorResources::Message::Message();
	logmsg->message = gcnew String(message.c_str());
	logmsg->type = EditorResources::Message::Message::MsgType::Error;
	auto msgargs = gcnew EditorResources::Functionality::EditorLogEventArgs();
	msgargs->logMessage = logmsg;
	EditorResources::Functionality::EditorEvents::OnLogEvent(msgargs);
#endif
}

void Logger::Severe(Core::String message)
{
	getLogger().log << "[SEVERE]\t" << message << std::endl;
#ifdef _EDITOR_
	auto logmsg = gcnew EditorResources::Message::Message();
	logmsg->message = gcnew String(message.c_str());
	logmsg->type = EditorResources::Message::Message::MsgType::Severe;
	auto msgargs = gcnew EditorResources::Functionality::EditorLogEventArgs();
	msgargs->logMessage = logmsg;
	EditorResources::Functionality::EditorEvents::OnLogEvent(msgargs);
#endif
}

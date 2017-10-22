#include "Logger.hpp"

#ifdef _EDITOR_
#include <EditorManager\EditorCore.hpp>
#endif

OneLogger* OneLogger::logger;
OneLogger::OneLogger() : log("Log.log")
{
}

OneLogger& OneLogger::getLogger()
{
	if (!logger)
		logger = new OneLogger();
	return *logger;
}

void OneLogger::free()
{
	delete logger;
}

void OneLogger::initialize()
{
	getLogger();
}

void OneLogger::Debug(Core::String message, Core::String filename, size_t line)
{
	OneLogger::Debug(message + " - " + filename + " (" + std::to_string(line) + ")");
}

void OneLogger::Info(Core::String message, Core::String filename, size_t line)
{
	OneLogger::Info(message + " - " + filename + " (" + std::to_string(line) + ")");
}

void OneLogger::Fine(Core::String message, Core::String filename, size_t line)
{
	OneLogger::Fine(message + " - " + filename + " (" + std::to_string(line) + ")");
}

void OneLogger::Warning(Core::String message, Core::String filename, size_t line)
{
	OneLogger::Warning(message + " - " + filename + " (" + std::to_string(line) + ")");
}

void OneLogger::Error(Core::String message, Core::String filename, size_t line)
{
	OneLogger::Error(message + " - " + filename + " (" + std::to_string(line) + ")");
}

void OneLogger::Severe(Core::String message, Core::String filename, size_t line)
{
	OneLogger::Severe(message + " - " + filename + " (" + std::to_string(line) + ")");
}

void OneLogger::Debug(Core::String message)
{
	getLogger().log << "[DEBUG]\t\t" << message << std::endl;
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Message::Message::MsgType::Debug);
#endif
}

void OneLogger::Info(Core::String message)
{
	getLogger().log << "[INFO]\t\t" << message << std::endl;
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Message::Message::MsgType::Info);
#endif
}

void OneLogger::Fine(Core::String message)
{
	getLogger().log << "[FINE]\t\t" << message << std::endl;
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Message::Message::MsgType::Fine);
#endif
}

void OneLogger::Warning(Core::String message)
{
	getLogger().log << "[WARNING]\t" << message << std::endl;
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Message::Message::MsgType::Warning);
#endif
}

void OneLogger::Error(Core::String message)
{
	getLogger().log << "[ERROR]\t\t" << message << std::endl;
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Message::Message::MsgType::Error);
#endif
}

void OneLogger::Severe(Core::String message)
{
	getLogger().log << "[SEVERE]\t" << message << std::endl;
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Message::Message::MsgType::Severe);
#endif
}


#ifdef _EDITOR_
void OneLogger::LogToEditor(Core::String message, EditorResources::Message::Message::MsgType MsgType)
{
#ifndef _UNITTESTS_
	auto logmsg = gcnew EditorResources::Message::Message();
	logmsg->message = gcnew String(message.c_str());
	logmsg->type = MsgType;
	auto msgargs = gcnew EditorResources::Functionality::EditorLogEventArgs();
	msgargs->logMessage = logmsg;
	EditorResources::Functionality::EditorEvents::OnLogEvent(msgargs);
#endif
}

#endif

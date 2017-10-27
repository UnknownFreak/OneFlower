#include "Logger.hpp"
#ifdef _WIN32
#include <direct.h>
#define getcwd _wgetcwd // stupid MSFT "deprecation" warning
#elif
#include <unistd.h>
#endif
#ifdef _EDITOR_
#include <EditorManager\EditorCore.hpp>
#endif

OneLogger* OneLogger::logger;
OneLogger::OneLogger() : log("Log.log")
{
#ifdef _WIN32
	wchar_t* c = getcwd(NULL, 0);
	if (c) // sneaky string breaks on char* = NULL
		cwd = Core::String(Core::Converter.toUtf8(std::wstring(c)));
#else
	char* c = getcwd(NULL, 0);
	if (c)
		cwd = Core::String(c);
#endif
	std::free(c);
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
	OneLogger::Debug(message + " - " + filename.replace(0, getLogger().cwd.size(), "") + " (" + std::to_string(line) + ")");
}

void OneLogger::Info(Core::String message, Core::String filename, size_t line)
{
	OneLogger::Info(message + " - " + filename.replace(0, getLogger().cwd.size(), "") + " (" + std::to_string(line) + ")");
}

void OneLogger::Fine(Core::String message, Core::String filename, size_t line)
{
	OneLogger::Fine(message + " - " + filename.replace(0, getLogger().cwd.size(), "") + " (" + std::to_string(line) + ")");
}

void OneLogger::Warning(Core::String message, Core::String filename, size_t line)
{
	OneLogger::Warning(message + " - " + filename.replace(0, getLogger().cwd.size(), "") + " (" + std::to_string(line) + ")");
}

void OneLogger::Error(Core::String message, Core::String filename, size_t line)
{
	OneLogger::Error(message + " - " + filename.replace(0, getLogger().cwd.size(), "") + " (" + std::to_string(line) + ")");
}

void OneLogger::Severe(Core::String message, Core::String filename, size_t line)
{
	OneLogger::Severe(message + " - " + filename.replace(0, getLogger().cwd.size(), "") + " (" + std::to_string(line) + ")");
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

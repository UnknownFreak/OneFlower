#include "Logger.hpp"
#ifdef _WIN32
#include <direct.h>
#define getcwd _wgetcwd // stupid MSFT "deprecation" warning
#elif
#include <unistd.h>
#endif
#ifdef _EDITOR_
#include <Editor\InteropHelper.hpp>
#endif

#ifdef ERROR // wingdi.h can have ERROR defined undef if it exists to prevent compile error and set flag to re-enable it afterwards
#undef ERROR
#define ERROR_UNDEF
#endif

#include <Core\EngineModule\EngineModuleManager.hpp>


ResourceType IEngineResource<OneLogger>::type = ResourceType::Logger;

Core::String OneLogger::DEBUG = "DEBUG\t\t";
Core::String OneLogger::INFO = "INFO\t\t";
Core::String OneLogger::FINE = "FINE\t\t";
Core::String OneLogger::WARNING = "WARNING\t\t";
Core::String OneLogger::ERROR = "ERROR\t\t";
Core::String OneLogger::CRITICAL = "CRITICAL\t";
Core::String OneLogger::SEPARATOR = " - ";
Core::String OneLogger::LINE_BEGIN = " (";
Core::String OneLogger::LINE_END = ")";

OneLogger::OneLogger() : log("Log.log")
{
#ifdef _WIN32
	wchar_t* c = getcwd(NULL, 0);
	if (c) // sneaky string breaks on wchar_t* = NULL
		cwd = Core::String(Engine::GetModule<Core::StringConverter>().toUtf8(std::wstring(c)));
#else
	char* c = getcwd(NULL, 0); // unix use utf-8 on their path encoding. So char* is fine.
	if (c)
		cwd = Core::String(c);
#endif
	std::free(c);
}

void OneLogger::DisableEditorLogging()
{
	logToEditor = false;
}

void OneLogger::Debug(Core::String message, Core::String filename, size_t line)
{
	Debug(message + SEPARATOR + filename.replace(0, cwd.size(), "") + LINE_BEGIN + std::to_string(line) + LINE_END);
}

void OneLogger::Info(Core::String message, Core::String filename, size_t line)
{
	Info(message + SEPARATOR + filename.replace(0, cwd.size(), "") + LINE_BEGIN + std::to_string(line) + LINE_END);
}

void OneLogger::Fine(Core::String message, Core::String filename, size_t line)
{
	Fine(message + SEPARATOR + filename.replace(0, cwd.size(), "") + LINE_BEGIN + std::to_string(line) + LINE_END);
}

void OneLogger::Warning(Core::String message, Core::String filename, size_t line)
{
	Warning(message + SEPARATOR + filename.replace(0, cwd.size(), "") + LINE_BEGIN + std::to_string(line) + LINE_END);
}

void OneLogger::Error(Core::String message, Core::String filename, size_t line)
{
	Error(message + SEPARATOR + filename.replace(0, cwd.size(), "") + LINE_BEGIN + std::to_string(line) + LINE_END);
}

void OneLogger::Critical(Core::String message, Core::String filename, size_t line)
{
	Critical(message + SEPARATOR + filename.replace(0, cwd.size(), "") + LINE_BEGIN + std::to_string(line) + LINE_END);
}

void OneLogger::Debug(Core::String message)
{
	logMessage(DEBUG, message);
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Utils::Message::MsgType::Debug);
#endif
}

void OneLogger::Info(Core::String message)
{
	logMessage(INFO, message);
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Utils::Message::MsgType::Info);
#endif
}

void OneLogger::Fine(Core::String message)
{
	logMessage(FINE, message);
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Utils::Message::MsgType::Fine);
#endif
}

void OneLogger::Warning(Core::String message)
{
	logMessage(WARNING, message);
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Utils::Message::MsgType::Warning);
#endif
}

void OneLogger::Error(Core::String message)
{
	logMessage(ERROR, message);
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Utils::Message::MsgType::Error);
#endif
}

void OneLogger::Critical(Core::String message)
{
	logMessage(CRITICAL, message);
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Utils::Message::MsgType::Critical);
#endif
}


#ifdef _EDITOR_
void OneLogger::LogToEditor(Core::String& message, EditorResources::Utils::Message::MsgType MsgType)
{
	if (!logToEditor)
		return;
#ifndef _UNITTESTS_
	auto logmsg = gcnew EditorResources::Utils::Message();
	logmsg->message = gcnew System::String(message.c_str());
	logmsg->type = MsgType;
	auto msgargs = gcnew EditorResources::Utils::EditorEvents::EditorLogEventArgs();
	msgargs->logMessage = logmsg;
	EditorResources::Utils::EditorEvents::OnLogEvent(msgargs);
#endif
}
#endif

void OneLogger::logMessage(Core::String & _type, Core::String & message)
{
	log << _type << message << std::endl;
}

#ifdef ERROR_UNDEF // re-enable ERROR 0 define for wingdi.h if it was defined
#define ERROR 0
#endif


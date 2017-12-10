#include "Logger.hpp"
#ifdef _WIN32
#include <direct.h>
#define getcwd _wgetcwd // stupid MSFT "deprecation" warning
#elif
#include <unistd.h>
#endif
#ifdef _EDITOR_
#include <EditorManager\InteropHelper.hpp>
#endif

#include <Core\IEngineResource\EngineResourceManager.hpp>

ResourceType IEngineResource<OneLogger>::type = ResourceType::Logger;

OneLogger::OneLogger() : log("Log.log")
{
#ifdef _WIN32
	wchar_t* c = getcwd(NULL, 0);
	if (c) // sneaky string breaks on wchar_t* = NULL
		cwd = Core::String(Engine::Get<Core::StringConverter>().toUtf8(std::wstring(c)));
#else
	char* c = getcwd(NULL, 0); // unix use utf-8 on their path encoding. So char* is fine.
	if (c)
		cwd = Core::String(c);
#endif
	std::free(c);
}

void OneLogger::Debug(Core::String message, Core::String filename, size_t line)
{
	Debug(message + " - " + filename.replace(0, cwd.size(), "") + " (" + std::to_string(line) + ")");
}

void OneLogger::Info(Core::String message, Core::String filename, size_t line)
{
	Info(message + " - " + filename.replace(0, cwd.size(), "") + " (" + std::to_string(line) + ")");
}

void OneLogger::Fine(Core::String message, Core::String filename, size_t line)
{
	Fine(message + " - " + filename.replace(0, cwd.size(), "") + " (" + std::to_string(line) + ")");
}

void OneLogger::Warning(Core::String message, Core::String filename, size_t line)
{
	Warning(message + " - " + filename.replace(0, cwd.size(), "") + " (" + std::to_string(line) + ")");
}

void OneLogger::Error(Core::String message, Core::String filename, size_t line)
{
	Error(message + " - " + filename.replace(0, cwd.size(), "") + " (" + std::to_string(line) + ")");
}

void OneLogger::Severe(Core::String message, Core::String filename, size_t line)
{
	Severe(message + " - " + filename.replace(0, cwd.size(), "") + " (" + std::to_string(line) + ")");
}

void OneLogger::Debug(Core::String message)
{
	log << "[DEBUG]\t\t" << message << std::endl;
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Message::Message::MsgType::Debug);
#endif
}

void OneLogger::Info(Core::String message)
{
	log << "[INFO]\t\t" << message << std::endl;
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Message::Message::MsgType::Info);
#endif
}

void OneLogger::Fine(Core::String message)
{
	log << "[FINE]\t\t" << message << std::endl;
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Message::Message::MsgType::Fine);
#endif
}

void OneLogger::Warning(Core::String message)
{
	log << "[WARNING]\t" << message << std::endl;
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Message::Message::MsgType::Warning);
#endif
}

void OneLogger::Error(Core::String message)
{
	log << "[ERROR]\t\t" << message << std::endl;
#ifdef _EDITOR_
	LogToEditor(message, EditorResources::Message::Message::MsgType::Error);
#endif
}

void OneLogger::Severe(Core::String message)
{
	log << "[SEVERE]\t" << message << std::endl;
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

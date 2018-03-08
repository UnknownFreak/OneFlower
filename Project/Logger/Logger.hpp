#ifndef LOGGER_HPP
#define LOGGER_HPP
#ifdef ERROR // wingdi.h can have ERROR defined undef if it exists to prevent compile error and set flag to re-enable it afterwards
	#undef ERROR
	#define ERROR_UNDEF
#endif

#include <fstream> 
#include <Core\IEngineResource\IEngineResource.hpp>
#include <Core\String.hpp>

class OneLogger : public IEngineResource<OneLogger> 
{

	static Core::String DEBUG;
	static Core::String INFO;
	static Core::String FINE;
	static Core::String WARNING;
	static Core::String ERROR;
	static Core::String CRITICAL;
	static Core::String SEPARATOR;
	static Core::String LINE_BEGIN;
	static Core::String LINE_END;

	std::ofstream log;

	Core::String cwd;

#ifdef _EDITOR_
	void LogToEditor(Core::String& message, EditorResources::Utils::Message::MsgType msgType);
#endif

	void logMessage(Core::String& type, Core::String& message);

	bool logToEditor = true;

public:
	OneLogger();

	const ResourceType& getType()
	{
		return type;
	}

	void DisableEditorLogging();

	void Debug(Core::String message, Core::String filename , size_t line);
	void Info(Core::String message, Core::String filename, size_t line);
	void Fine(Core::String message, Core::String filename, size_t line);
	void Warning(Core::String message, Core::String filename, size_t line);
	void Error(Core::String message, Core::String filename, size_t line);
	void Critical(Core::String message, Core::String filename, size_t line);

	void Debug(Core::String message);
	void Info(Core::String message);
	void Fine(Core::String message);
	void Warning(Core::String message);
	void Error(Core::String message);
	void Critical(Core::String message);

};
#ifdef ERROR_UNDEF // re-enable ERROR 0 define for wingdi.h if it was defined
	#define ERROR 0
#endif
#endif

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <Core\String.hpp>
#include <fstream>
class OneLogger
{
	static OneLogger* logger;

	OneLogger();

	static OneLogger& getLogger();
	
	std::ofstream log;
#ifdef _EDITOR_
	static void LogToEditor(Core::String message, EditorResources::Message::Message::MsgType msgType);
#endif
public:

	static void free();
	static void initialize();

	static void Debug(Core::String message, Core::String filename , size_t line);
	static void Info(Core::String message, Core::String filename, size_t line);
	static void Fine(Core::String message, Core::String filename, size_t line);
	static void Warning(Core::String message, Core::String filename, size_t line);
	static void Error(Core::String message, Core::String filename, size_t line);
	static void Severe(Core::String message, Core::String filename, size_t line);

	static void Debug(Core::String message);
	static void Info(Core::String message);
	static void Fine(Core::String message);
	static void Warning(Core::String message);
	static void Error(Core::String message);
	static void Severe(Core::String message);

};

#endif

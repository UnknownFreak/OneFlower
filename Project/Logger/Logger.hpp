#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream> 
#include <Core\IEngineResource\IEngineResource.hpp>
#include <Core\String.hpp>

class OneLogger : public IEngineResource<OneLogger> 
{

	std::ofstream log;

	Core::String cwd;

#ifdef _EDITOR_
	static void LogToEditor(Core::String message, EditorResources::Message::Message::MsgType msgType);
#endif
public:
	OneLogger();

	const ResourceType& getType()
	{
		return type;
	}


	void Debug(Core::String message, Core::String filename , size_t line);
	void Info(Core::String message, Core::String filename, size_t line);
	void Fine(Core::String message, Core::String filename, size_t line);
	void Warning(Core::String message, Core::String filename, size_t line);
	void Error(Core::String message, Core::String filename, size_t line);
	void Severe(Core::String message, Core::String filename, size_t line);

	void Debug(Core::String message);
	void Info(Core::String message);
	void Fine(Core::String message);
	void Warning(Core::String message);
	void Error(Core::String message);
	void Severe(Core::String message);

};



#endif

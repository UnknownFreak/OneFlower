#include "Console.hpp"

#include <iostream>
#include <Module/ModuleManager.hpp>
#include <Module/Logger/OneLogger.hpp>

#include <Graphics/Window.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<Console>::type = of::module::EngineResourceType::Console;

Console::Console() : currentText(), lines()
{
	
}

void Console::addCharacter(const char& s)
{
	currentText += s;
	textLine = caret +currentText;
}

void Console::removeLastCharacter()
{
	if(currentText.length())
		currentText.pop_back();
	textLine = caret + currentText;
}

void Console::write(const of::common::String& theLine, const bool& forcePopup)
{
	insertionLock.lock();
	lines.push_back(theLine);
	insertionLock.unlock();
	if (forcePopup)
	{
		of::engine::GetModule<Graphics::UI::UIHandler>().ShowConsole();
	}
}

void Console::registerCommand(const of::common::String& command, std::function<void(const of::common::String&)> commandFunc)
{
	commands[command] = commandFunc;
}

bool Console::execute()
{
	insertionLock.lock();
	lines.push_back(textLine);
	insertionLock.unlock();
	of::common::String commandString = textLine;

	auto command = commandString.substr(caret.length(), commandString.find(" ", 2) - caret.length());
	if (commands.find(command) != commands.end())
	{
		commands[command](commandString.substr(caret.length() + 1 + commandString.find(" ", 2) - caret.length()));
	}

	// PARSE TEXT AND EXEC COMMAND
	currentText.clear();
	textLine = caret;
	return false;
}

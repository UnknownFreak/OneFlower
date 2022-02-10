#include "Console.hpp"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Module/EngineModuleManager.hpp>
#include <Module/Logger/OneLogger.hpp>

#include <Graphics/Window.hpp>

Enums::EngineResourceType Interfaces::IEngineResource<Console>::type = Enums::EngineResourceType::Console;

void Console::formatLines()
{
	float incr = 600.f;
	for (auto it = lines.rbegin(); it != lines.rend(); ++it)
	{
		incr -= 13.f;
		it->setPosition({ 4.f, incr });
	}
}

Console::Console() : currentText(), lines()
{
	if (!consoleFont.loadFromFile(Core::SystemFonts + "arial.ttf"))
	{
		if (!consoleFont.loadFromFile(Core::SystemFonts + "consolas.ttf"))
		{
			Engine::GetModule < EngineModule::Logger::OneLogger >().getLogger("Console").Error("Unable to load font for Console!");
		}
	}
	textLine.setFont(consoleFont);
	textLine.setFillColor(sf::Color::White);
	textLine.setCharacterSize(12);
	textLine.setPosition({ 4, 600 });
	textLine.setString(caret);
}

void Console::addCharacter(const char& s)
{
	currentText += s;
	textLine.setString(caret + sf::String(currentText));
}

void Console::removeLastCharacter()
{
	if(currentText.length())
		currentText.pop_back();
	textLine.setString(caret + sf::String(currentText));
}

void Console::write(const Core::String& theLine, const bool& forcePopup)
{
	insertionLock.lock();
	lines.push_back(sf::Text(theLine, consoleFont, 12));
	formatLines();
	insertionLock.unlock();
	if (forcePopup)
	{
		Engine::GetModule<Graphics::UI::UIHandler>().ShowConsole();
	}
}

void Console::registerCommand(const Core::String& command, std::function<void(const Core::String&)> commandFunc)
{
	commands[command] = commandFunc;
}

bool Console::execute()
{
	insertionLock.lock();
	lines.push_back(textLine);
	formatLines();
	insertionLock.unlock();
	Core::String commandString = textLine.getString();

	auto command = commandString.substr(caret.length(), commandString.find(" ", 2) - caret.length());
	if (commands.find(command) != commands.end())
	{
		commands[command](commandString.substr(caret.length() + 1 + commandString.find(" ", 2) - caret.length()));
	}

	// PARSE TEXT AND EXEC COMMAND
	currentText.clear();
	textLine.setString(caret);
	return false;
}

void Console::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(textLine, states);
	size_t counter = 0;
	if (insertionLock.try_lock())
	{
		for (auto it = lines.rbegin(); it != lines.rend(); ++it)
		{
			target.draw(*it, states);
			counter++;
			if (counter >= max_lines)
			{
				insertionLock.unlock();
				return;

			}
		}
		insertionLock.unlock();

	}
}

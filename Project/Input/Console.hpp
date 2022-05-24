#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <vector>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <Interfaces\IEngineModule.hpp>
#include <Helpers/String.hpp>


class Console : public Interfaces::IEngineResource<Console>
{
	mutable std::mutex insertionLock;
	const size_t max_lines = 45;
	const Core::String caret = "> ";
	std::vector<Core::String> lines;
	Core::String currentText;
	Core::String textLine;

	std::unordered_map<Core::String, std::function<void(const Core::String& args)>> commands;

public:

	Console();

	void addCharacter(const char& s);
	void removeLastCharacter();
	void write(const Core::String& theLine, const bool& forcePopup);

	void registerCommand(const Core::String& command, std::function<void(const Core::String&)> commandFunc);

	bool execute();

	// Inherited via IEngineResource
	virtual Enums::EngineResourceType& getType() const override { return type; }


};

#endif
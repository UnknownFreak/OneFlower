#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <vector>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <Interfaces\IEngineModule.hpp>
#include <utils/common/string.hpp>


class Console : public Interfaces::IEngineResource<Console>
{
	mutable std::mutex insertionLock;
	const size_t max_lines = 45;
	const of::common::String caret = "> ";
	std::vector<of::common::String> lines;
	of::common::String currentText;
	of::common::String textLine;

	std::unordered_map<of::common::String, std::function<void(const of::common::String& args)>> commands;

public:

	Console();

	void addCharacter(const char& s);
	void removeLastCharacter();
	void write(const of::common::String& theLine, const bool& forcePopup);

	void registerCommand(const of::common::String& command, std::function<void(const of::common::String&)> commandFunc);

	bool execute();

	// Inherited via IEngineResource
	virtual Enums::EngineResourceType& getType() const override { return type; }


};

#endif
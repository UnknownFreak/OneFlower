#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <vector>
#include <mutex>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <Interfaces\IEngineModule.hpp>
#include <Helpers/String.hpp>


class Console : public Interfaces::IEngineResource<Console>, public sf::Drawable
{
	mutable std::mutex insertionLock;
	const size_t max_lines = 45;
	const Core::String caret = "> ";
	std::vector<sf::Text> lines;
	Core::String currentText;

	sf::Font consoleFont;
	sf::Text textLine;

	void formatLines();

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


	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif
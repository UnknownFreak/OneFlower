#include "UIHandler.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Mouse.hpp>


Enums::EngineResourceType Interfaces::IEngineResource<Graphics::UI::UIHandler>::type = Enums::EngineResourceType::UIHandler;

namespace Graphics::UI
{
	void UIHandler::ToggleConsole()
	{
		consoleEnabled = !consoleEnabled;
	}

	void UIHandler::ShowConsole()
	{
		consoleEnabled = true;
	}

	void UIHandler::addUIContext(const Enums::UIContextNames& contextName, std::unique_ptr<UIContext> context)
	{
		auto& logger =Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Graphics::UI::UIHandler");
		logger.Debug("Adding UI Context ", context->uiName);
		uiContext.emplace(contextName, std::move(context));
	}

	void UIHandler::removeUIContext(const Enums::UIContextNames& contextName)
	{
		uiToRemove.push_back(contextName);
	}

	void UIHandler::updateMouse(const sf::RenderWindow& window)
	{
		auto m = sf::Mouse::getPosition(window);
		mouse = { float(m.x), float(m.y) };
	}

	void UIHandler::toggleToolTips() const
	{
		for (const auto& ui : uiContext)
		{
			if (ui.first == Enums::UIContextNames::FPS || ui.first == Enums::UIContextNames::UPS)
			{
			}
			else
			{
				ui.second.get()->onMouseHover(mouse);
				ui.second.get()->update();
			}
		}
	}
	bool UIHandler::isContextAvailable(const Enums::UIContextNames& name)
	{
		return uiContext.find(name) != uiContext.end();
	}

	void UIHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for(const auto name : uiToRemove)
		{
			std::map<Enums::UIContextNames, std::unique_ptr<UIContext>>& x = const_cast<std::map<Enums::UIContextNames, std::unique_ptr<UIContext>>&>(uiContext);
			//Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Graphics::UI").Debug("Removing UI Context ", name);
			x.erase(name);
		}
		const_cast<std::vector<Enums::UIContextNames>&>(uiToRemove).clear();
		for(auto& x : uiContext)
		{
			if (showLoadingScreenOnly)
			{
				if (x.first < Enums::UIContextNames::LoadingScreen)
				{
					target.draw(*x.second.get(), states);
				}
			}
			else
			{
				target.draw(*x.second.get(), states);

			}
		}
		if (consoleEnabled)
		{
			target.draw(rs, states);
			target.draw(console);
		}
	}
}
#ifndef UIHandler_HPP
#define UIHandler_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Module/EngineModuleManager.hpp>
#include <Interfaces/IEngineModule.hpp>

#include <vector>
#include <Input/Console.hpp>
#include <Helpers/Enum/UIContextNames.hpp>
#include "UIContext.hpp"

namespace Graphics::UI
{

	class UIHandler : public Interfaces::IEngineResource<UIHandler>, sf::Drawable
	{
		Core::Vector2f mouse;
		std::vector<Enums::UIContextNames> uiToRemove;
		std::map<Enums::UIContextNames, std::unique_ptr<UIContext>> uiContext;

		bool consoleEnabled = false;

		sf::RectangleShape rs;

		Console& console;

	public:

		bool showLoadingScreenOnly;

		UIHandler() : console(Engine::GetModule<Console>())
		{
			rs.setPosition(0, 0);
			rs.setSize({1920, 620 });
			rs.setFillColor(sf::Color(100, 100, 100, 20));
		};

		~UIHandler() = default;

		void ToggleConsole();
		void ShowConsole();
		void addUIContext(const Enums::UIContextNames&, std::unique_ptr<UIContext> context);
		void removeUIContext(const Enums::UIContextNames& contextName);
		void updateMouse(const sf::RenderWindow& window);
		void toggleToolTips() const;

		template <class Ty>
		Ty* getUIContext(const Enums::UIContextNames& name)
		{
			return (Ty*)uiContext[name].get();
		}

		Enums::EngineResourceType& getType() const
		{
			return type;
		}
		
		bool isContextAvailable(const Enums::UIContextNames& name);
		

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}

#endif
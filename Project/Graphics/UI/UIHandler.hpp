#ifndef UIHandler_HPP
#define UIHandler_HPP

#include <module/ModuleManager.hpp>
#include <module/IEngineModule.hpp>

#include <vector>
#include <Input/Console.hpp>
#include <Helpers/Enum/UIContextNames.hpp>
#include "UIContext.hpp"

namespace Graphics::UI
{

	class UIHandler : public of::module::interface::IEngineResource<UIHandler>
	{
		glm::vec2 mouse;
		std::vector<Enums::UIContextNames> uiToRemove;
		std::map<Enums::UIContextNames, std::unique_ptr<UIContext>> uiContext;

		bool consoleEnabled = false;

		Console& console;

	public:

		bool showLoadingScreenOnly;

		UIHandler() : console(of::engine::GetModule<Console>())
		{
		};

		~UIHandler() = default;

		void ToggleConsole();
		void ShowConsole();
		void addUIContext(const Enums::UIContextNames&, std::unique_ptr<UIContext> context);
		void removeUIContext(const Enums::UIContextNames& contextName);
		void toggleToolTips() const;

		template <class Ty>
		Ty* getUIContext(const Enums::UIContextNames& name)
		{
			return (Ty*)uiContext[name].get();
		}

		of::module::EngineResourceType& getType() const
		{
			return type;
		}
		
		bool isContextAvailable(const Enums::UIContextNames& name);
		
		void render();

	};
}

#endif
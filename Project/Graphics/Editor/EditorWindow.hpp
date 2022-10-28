#ifndef EditorWindow_HPP
#define EditorWindow_HPP

#include <Graphics/UI/UIContext.hpp>
#include "NewFileModal.hpp"
#include "LoadFileModal.hpp"
#include "DataTree.hpp"

namespace Graphics
{
	namespace Editor
	{

		class MainEditorWindow : public Graphics::UI::UIContext
		{
			Modals::NewFile newFileModal;
			Modals::LoadFile loadFileModal;
			DataTree tree;
			unsigned width, height;

			void renderMenuBar();

		public:

			void setSize(const unsigned& width, const unsigned& height);

			MainEditorWindow();

			// Inherited via UIContext
			virtual void onMouseHover(const glm::vec2& mouse) override;
			virtual void readInput() override;
			virtual void render() override;
		};

	}
}

#endif
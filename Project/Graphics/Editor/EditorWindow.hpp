#ifndef EditorWindow_HPP
#define EditorWindow_HPP

#include <Graphics/UI/UIContext.hpp>
#include "NewFileModal.hpp"
#include "LoadFileModal.hpp"
#include "DataTree.hpp"
#include <graphics/parentedRenderable.hpp>

namespace Graphics
{
	namespace Editor
	{

		class MainEditorWindow : public Graphics::UI::UIContext, public of::graphics::ParentedRenderable
		{
			Modals::NewFile newFileModal;
			Modals::LoadFile loadFileModal;
			DataTree tree;
			float width, height;

			void renderMenuBar();

		public:

			void setSize(const unsigned& width, const unsigned& height);

			MainEditorWindow();

			// Inherited via UIContext
			virtual void onMouseHover(const glm::vec2& mouse) override;
			virtual void readInput() override;
			virtual void render() override;

			// Inherited via ParentedRenderable
			virtual void updateFrame(const float& dt) override;
			virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp) override;
		};

	}
}

#endif
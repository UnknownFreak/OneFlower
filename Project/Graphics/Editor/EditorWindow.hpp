#ifndef EditorWindow_HPP
#define EditorWindow_HPP

#include <Graphics/UI/UIContext.hpp>

namespace Graphics
{
	namespace Editor
	{

		class MainEditorWindow : public Graphics::UI::UIContext
		{
			unsigned width, height;
			bool test;
			bool test2;
		public:

			MainEditorWindow();

			// Inherited via UIContext
			virtual void onMouseHover(const glm::vec2& mouse) override;
			virtual void readInput() override;
			virtual void render() override;
		};

	}
}

#endif
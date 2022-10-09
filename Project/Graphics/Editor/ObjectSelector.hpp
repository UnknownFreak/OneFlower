#ifndef ObjectSelector_HPP
#define ObjectSelector_HPP

#include <Object/GameObject.hpp>
#include <map>

#include <Graphics/UI/UIContext.hpp>

namespace Graphics
{
	namespace Editor
	{

		class ObjectSelector : public Graphics::UI::UIContext
		{
			std::map<GameObject*, bool> objects;
			GameObject* selected = nullptr;
		public:
			ObjectSelector();


			// Inherited via UIContext
			virtual void onMouseHover(const glm::vec2&) override {};

			virtual void readInput() override {};

			virtual void render() override;

		};

	}
}

#endif
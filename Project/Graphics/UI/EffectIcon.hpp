#ifndef EffectIcon_HPP
#define EffectIcon_HPP

#include <swizzle/gfx/Texture.hpp>

#include "UIContext.hpp"
#include "PlainToolTip.hpp"

#include <Combat/EffectStack.hpp>


namespace Graphics::UI
{
	class EffectIcon : public UIContext
	{
		PlainToolTip toolTip;
		glm::vec2 pos;
		std::shared_ptr<swizzle::gfx::Texture> iconTexture;
		Combat::EffectStack& stack;
		//sf::Vertex vertex[4];
		//sf::VertexBuffer buf;

	public:
		glm::vec2 iconSize;

		EffectIcon(const of::common::String& icon, Combat::EffectStack& stack);


		void updatePos(const glm::vec2& pos);
		// Inherited via UIContext
		virtual void onMouseHover(const glm::vec2& mouse) override;
		virtual void readInput() override;

		virtual void render() override;
	};
}

#endif
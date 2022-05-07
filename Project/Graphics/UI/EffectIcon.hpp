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
		Core::Vector2f pos;
		std::shared_ptr<swizzle::gfx::Texture> iconTexture;
		Combat::EffectStack& stack;
		//sf::Vertex vertex[4];
		//sf::VertexBuffer buf;

	public:
		Core::Vector2f iconSize;

		EffectIcon(const Core::String& icon, Combat::EffectStack& stack);


		void updatePos(const Core::Vector2f& pos);
		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f& mouse) override;
		virtual void readInput() override;

		virtual void render() override;
	};
}

#endif
#ifndef LoadingScreenInfo_HPP
#define LoadingScreenInfo_HPP

#include "UIContext.hpp"

#include <world/LoadingStateInfo.hpp>
#include <graphics/parentedRenderable.hpp>

namespace Graphics::UI
{

	class LoadingScreenInfo : public Graphics::UI::UIContext, public of::graphics::ParentedRenderable
	{
		of::common::String t;
		ImVec2 pos;

		of::world::LoadingStateInfo& info;

	public:

		LoadingScreenInfo();

		// Inherited via UIContext
		virtual void readInput() override;
		virtual void render() override;
		virtual void update() override;

		// Inherited via UIContext
		virtual void onMouseHover(const glm::vec2& mouse) override;

		// Inherited via ParentedRenderable
		virtual void updateFrame(const float& dt) override;
		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp) override;
	};
}

#endif
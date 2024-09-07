#pragma once

#include <scene/LoadingStateInfo.hpp>
#include <graphics/parentedRenderable.hpp>

namespace of::scene::imgui
{

	class LoadingScreenInfo : public of::graphics::ParentedRenderable
	{
		of::common::String t;
		bool visible;
		ImVec2 pos;

		of::world::LoadingStateInfo& mInfo;

	public:

		LoadingScreenInfo(of::world::LoadingStateInfo& info);

		// Inherited via ParentedRenderable
		virtual void updateFrame(const float dt) override;
		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& transaction, of::graphics::view::MVP& mvp) override;
	};
}

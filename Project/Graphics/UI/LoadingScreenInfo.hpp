#ifndef LoadingScreenInfo_HPP
#define LoadingScreenInfo_HPP

#include "UIContext.hpp"

#include <world/LoadingStateInfo.hpp>

namespace Graphics::UI
{

	class LoadingScreenInfo : public Graphics::UI::UIContext
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
	};
}

#endif
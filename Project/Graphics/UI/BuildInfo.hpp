#ifndef BUILDINFO_HPP
#define BUILDINFO_HPP

#include "UIContext.hpp"

#include <Helpers/String.hpp>

namespace Graphics::UI
{

	class BuildInfo : public Graphics::UI::UIContext
	{
		float x, y;
		Core::String t;

	public:
		BuildInfo(const Core::String info = "Null", float x = 0.f, float y = 0.f) : UIContext(swizzle::input::Keys::KeyF3, info, false), x(x), y(y) {
			t = info;
		}

		BuildInfo(const BuildInfo& copy) : BuildInfo(copy.t, copy.x, copy.y)
		{
		}
		
		// Inherited via Drawable
		virtual void render() override
		{
			if (visible)
			{
				ImGui::SetNextWindowPos(ImVec2{ x,y });
				ImGui::Begin("BuildInfo", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoInputs);
				ImGui::Text("%s", t.c_str());
				ImGui::End();
			}
		}

		// Inherited via UIContext
		virtual void readInput() override {};

		// Inherited via UIContext
		virtual void onMouseHover(const Core::Vector2f&) override {};
	};
}

#endif 

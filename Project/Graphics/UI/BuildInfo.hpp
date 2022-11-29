#ifndef BUILDINFO_HPP
#define BUILDINFO_HPP

#include "UIContext.hpp"

#include <utils/common/string.hpp>

namespace Graphics::UI
{

	class BuildInfo : public Graphics::UI::UIContext
	{
		of::common::String t;

	public:
		BuildInfo(const of::common::String info = "Null", float x = 0.f, float y = 0.f) : UIContext(swizzle::input::Keys::KeyF3, info, false) {
			t = info;
			this->x = x;
			this->y = y;
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
				ImGui::SetNextWindowBgAlpha(0.f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
				ImGui::Begin("BuildInfo", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_::ImGuiWindowFlags_NoInputs);
				ImGui::Text("%s", t.c_str());
				ImGui::End();
				ImGui::PopStyleVar();
			}
		}

		// Inherited via UIContext
		virtual void readInput() override {};

		// Inherited via UIContext
		virtual void onMouseHover(const glm::vec2&) override {};
	};
}

#endif 

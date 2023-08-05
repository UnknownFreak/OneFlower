#ifndef BUILDINFO_HPP
#define BUILDINFO_HPP

#include "UIContext.hpp"

#include <utils/common/string.hpp>
#include <graphics/parentedRenderable.hpp>

namespace Graphics::UI
{

	class BuildInfo : public Graphics::UI::UIContext, public of::graphics::ParentedRenderable
	{
		of::common::String t;
		float offsetX;
		float offsetY;
		Rel rel;
	public:
		BuildInfo(const of::common::String info = "Null", float x = 0.f, float y = 0.f, Rel rel = Rel::Left) : UIContext(swizzle::input::Keys::KeyF3, info, false), offsetX(x), offsetY(y), rel(rel) {
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
				auto vp = ImGui::GetWindowViewport();
				ImGui::SetNextWindowPos(ImVec2{ vp->Pos.x + x, vp->Pos.y + y }, ImGuiCond_::ImGuiCond_Once);
				ImGui::SetNextWindowBgAlpha(0.f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
				ImGui::Begin("BuildInfo", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_::ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDocking);
				ImGui::Text("%s", t.c_str());
				ImGui::End();
				ImGui::PopStyleVar();
			}
		}

		// Inherited via UIContext
		virtual void readInput() override {};

		// Inherited via UIContext
		virtual void onMouseHover(const glm::vec2&) override {};

		// Inherited via ParentedRenderable
		virtual void updateFrame(const float&) override
		{
			y = offsetY;
			if (rel == Rel::Left)
			{
				x = offsetX;
			}
			else
			{
				x = m_parent->getWindowWidth() - offsetX;
			}
		};
		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>&, of::graphics::view::MVP&) override { render(); };
	};
}

#endif 

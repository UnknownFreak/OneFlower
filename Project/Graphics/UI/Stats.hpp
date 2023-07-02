#ifndef STATS_HPP
#define STATS_HPP

#include "UIContext.hpp"

#include <utils/common/string.hpp>

#include <utils/FpsCounter.hpp>
#include <utils/HighResolutionClock.hpp>

#include <imgui/imgui.h>
#include <graphics/parentedRenderable.hpp>

namespace Graphics::UI
{

	class Stats : public Graphics::UI::UIContext, public of::graphics::ParentedRenderable
	{
		U32 minFrame;
		U32 maxFrame;
		U32 mean[50] = { 0 };

		unsigned counterMax = 1;
		unsigned counter = 0;

		U32 mFrame;
		U32 mFps;
		const of::common::String title;
		of::common::String text = "";

		::utils::HighResolutionClock mClock;
		::utils::FpsCounter frameCounter;

		float previous;
		float current;
		Rel rel;
		float offsetX;
		float offsetY;
	public:
		Stats(const of::common::String text = "FPS", float x = 0.f, float y = 0.f, Rel rel = Rel::Left) : UIContext(swizzle::input::Keys::KeyF3, text, false), mFrame(0), mFps(0), title(text), minFrame(1000000), maxFrame(0), rel(rel), offsetX(x), offsetY(y)
		{
			previous = current = mClock.secondsAsFloat(false);
			this->x = x;
			this->y = y;
		}

		Stats(const Stats& copy) : Stats(copy.text, copy.x, copy.y)
		{
		}

		void tiq()
		{
			frameCounter.tick(current);
		}

		void update()
		{

			{
				current = mClock.secondsAsFloat(true);
				frameCounter.tick(current);
				mFps = frameCounter.getFps();
				previous = current;
				if (mFps > maxFrame)
					maxFrame = mFps;
				if (mFps < minFrame && mFps > 0)
					minFrame = mFps;
				mean[counter++] = mFps;
				counterMax++;
				if (counterMax > 50)
					counterMax = 50;
				if (counterMax < 0)
					counterMax = 0;
				if (counter > 50)
					counter = 0;
			}

		}
		void print()
		{
			{
				float avg = 0.f;
				for (unsigned c = 0; c < counterMax; c++)
					avg += mean[c];

				avg /= counterMax;
				text = of::common::String(title + ": " + std::to_string(mFps) + "\nmin: " + std::to_string(minFrame) + "\nmax: " + std::to_string(maxFrame) + "\navg: " + std::to_string(avg) + "\nms: " + std::to_string(1 / avg * 1000));
			}
		}

		// Inherited via Drawable
		virtual void render() override
		{
			if (visible)
			{
				ImGui::SetNextWindowPos(ImVec2{ x,y });
				ImGui::SetNextWindowBgAlpha(0.f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
				ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_::ImGuiWindowFlags_NoInputs);
				ImGui::Text("%s", text.c_str());
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
		virtual void render(std::unique_ptr<swizzle::gfx::DrawCommandTransaction>& , of::graphics::view::MVP& ) override { render(); };
	};
}

#endif 

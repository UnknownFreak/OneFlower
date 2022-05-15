#ifndef STATS_HPP
#define STATS_HPP

#include "UIContext.hpp"

#include <Helpers/String.hpp>

#include <utils/FpsCounter.hpp>

#include <imgui/imgui.h>

namespace Graphics::UI
{

	class Stats : public Graphics::UI::UIContext
	{
		float x, y;
		U32 minFrame;
		U32 maxFrame;
		U32 mean[50];

		unsigned counterMax = 1;
		unsigned counter = 0;

		U32 mFrame;
		U32 mFps;
		const Core::String title;
		Core::String text = "";

		utils::HighResolutionClock mClock;
		utils::FpsCounter frameCounter;

		float previous;
		float current;
	public:
		Stats(const Core::String text = "FPS", float x = 0.f, float y = 0.f) : UIContext(swizzle::input::Keys::KeyF3, text, false), mFrame(0), mFps(0), title(text), minFrame(1000000), maxFrame(0),
		x(x), y(y) {
			previous = current = mClock.secondsAsFloat(false);
		}

		Stats(const Stats& copy) : Stats(copy.text, copy.x, copy.y)
		{
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
				text = Core::String(title + ": " + std::to_string(mFps) + "\nmin: " + std::to_string(minFrame) + "\nmax: " + std::to_string(maxFrame) + "\navg: " + std::to_string(avg) + "\nms: " + std::to_string(1 / avg * 1000));
			}
		}

		// Inherited via Drawable
		virtual void render() override
		{
			if (visible)
			{
				ImGui::SetNextWindowPos(ImVec2{ x,y });
				ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoInputs);
				ImGui::Text("%s", text.c_str());
				ImGui::End();
				}
		}

		// Inherited via UIContext
		virtual void readInput() override {};

		// Inherited via UIContext
		virtual void onMouseHover(const glm::vec2&) override {};
	};
}

#endif 

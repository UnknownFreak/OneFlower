#include <imgui/sequencer.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <imgui/shapes.hpp>

#include <format>

namespace of::imgui
{
	static InternalSequencerInfo sequencerInfo{};
	static float currentTrackWidth = 0.f;
	static float lastTrackWidth = 0.f;
	static float nextTrackOffset = 0.f;

	// Local helper functions

	ImVec2 GetCursorPos()
	{
		ImGuiWindow* window = ImGui::GetCurrentWindowRead();
		return window->DC.CursorPos;
	}

	float GetLastCursorPosX()
	{
		ImGuiWindow* window = ImGui::GetCurrentWindowRead();
		return window->DC.CursorPosPrevLine.x - window->Pos.x + window->Scroll.x;
	}

	float GetLastCursorPosY()
	{
		ImGuiWindow* window = ImGui::GetCurrentWindowRead();
		return window->DC.CursorPosPrevLine.y - window->Pos.y + window->Scroll.y;
	}

	float calculateX(float& value, const float& limiter = 0.f)
	{
		const float newTimeLineSize = sequencerInfo.timelineSize;
		float zeroedOffset = newTimeLineSize / *sequencerInfo.timelineEndOffset;

		if (value < limiter)
			value = limiter;

		if (*sequencerInfo.timelineStart < 0)
		{
			zeroedOffset *= -1;
		}

		const float actualWidthToWorkWith = newTimeLineSize - zeroedOffset;

		float factor = 0.f;
		{
			factor = (value - *sequencerInfo.timelineStart) / *sequencerInfo.timelineEndOffset;
		}
		return  (actualWidthToWorkWith * factor);
	}

	// End local helper functions

	namespace internal
	{

		bool SequencerAddTrack()
		{
			return ImGui::SmallButton("+");
		}

		bool AddEventLine(const char* id)
		{
			std::string s = "+##";
			s += id;
			return ImGui::SmallButton(s.c_str());
		}

		void DrawHorizontalLine(const bool& addPadding, const ImColor& color, const float& padding)
		{
			auto pos = GetCursorPos();
			auto drawList = ImGui::GetWindowDrawList();
			drawList->AddLine({ pos.x - 12.f, pos.y }, { pos.x + ImGui::GetWindowWidth() + 4.f - padding, pos.y }, color);
			if (addPadding)
			{
				ImGui::Dummy({ 0, 2.f });
			}
		}

		void drawDivider(const float& dividerPos, const float& thickness)
		{
			auto pos = ImGui::GetWindowPos();
			auto drawList = ImGui::GetWindowDrawList();

			drawList->AddLine({ pos.x + dividerPos, pos.y }, { pos.x + dividerPos, pos.y + ImGui::GetWindowHeight() }, ImColor(0.f, 0.f, 0.f), thickness);
		}

		void DrawTrackLine(const float& start, const float& end, const ImColor& color, bool small)
		{
			auto min = GetCursorPos();
			auto drawList = ImGui::GetWindowDrawList();

			float y = 0;

			if (small)
				y = -4.f;
			drawList->AddRectFilled({ min.x + start, min.y - y - 2.f }, { min.x + end , min.y + y + 14.f }, color);
		}

		void DrawDiamond(const char* id, float& x, const float& min, const float& max)
		{
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems)
				return;

			auto pos = GetCursorPos();
			float newX = calculateX(x, sequencerInfo.startFrame) + sequencerInfo.centerLineOffset;

			float yPos = pos.y + 6.f;
			float xPos = pos.x + newX;

			float size = 8.f;

			ImRect bb = { {xPos - size, yPos - size }, {xPos + size, yPos + size} };

			auto _id = window->GetID(id);
			bool hovered;
			bool held;

			ImGui::ButtonBehavior(bb, _id, &hovered, &held);
			if (held)
			{
				x += ImGui::GetIO().MouseDelta.x * (*sequencerInfo.timelineEndOffset / 1500.f);
			}

			if (x < min)
			{
				x = min;
			}
			if (x > max)
			{
				x = max;
			}

			const ImColor color = hovered ? ImColor(0.3f, 0.3f, 0.3f) : ImColor(0.3f, 0.3f, 0.3f);

			newX = calculateX(x, sequencerInfo.startFrame) + sequencerInfo.centerLineOffset;
			xPos = pos.x + newX;

			DrawDiamondShape({ xPos, yPos }, size);
		}

		void drawTrackerLine(float line)
		{
			auto min = GetCursorPos();
			auto drawList = ImGui::GetWindowDrawList();

			drawList->AddLine(
				{ min.x + line + 14.f, min.y - 2.f },
				{ min.x + line + 14.f, min.y + ImGui::GetWindowHeight() + ImGui::GetScrollY() },
				ImColor(0.f, 0.f, 0.f).operator unsigned int(),
				3.f);
			drawList->AddLine(
				{ min.x + line + 14.f, min.y - 2.f },
				{ min.x + line + 14.f, min.y + ImGui::GetWindowHeight() + ImGui::GetScrollY() },
				ImColor(0.3f, 0.3f, 0.8f).operator unsigned int(),
				1.f);
		}

		void drawTracker(float& trackerPoint)
		{
			if (trackerPoint < *sequencerInfo.timelineStart)
			{
				return;
			}
			float trackerPointX = calculateX(trackerPoint);

			ImGui::SameLine();
			ImGui::SetCursorPosX(IM_FLOOR(trackerPointX) - 2.f);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.8f, 1.f));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.f, 0.f, 1.f));
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.2f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.f);
			ImGui::Button(std::format("{:.0f}", trackerPoint).c_str(), { 34.f, 0.f });

			if (ImGui::IsItemClicked())
			{
				sequencerInfo.isTrackSliderPressed = true;
			}

			if (sequencerInfo.isTrackSliderPressed && ImGui::GetIO().MouseDown[0])
			{
				trackerPoint += ImGui::GetIO().MouseDelta.x * (*sequencerInfo.timelineEndOffset / 1500.f);
			}
			else
			{
				sequencerInfo.isTrackSliderPressed = false;
			}

			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar(2);

			if (trackerPoint < 0)
			{
				trackerPoint = 0;
			}
		}

		void drawTimeLine(const float start, const float& endOffset, const float& workRangeStart, const float& workRangeEnd)
		{

			float itemWidth = ImGui::GetWindowWidth() / endOffset;
			float stepSize = 1.f;

			if (itemWidth > 50)
			{
				stepSize = 1.f;
			}
			else if (itemWidth > 30)
			{
				stepSize = 2.f;
			}
			else if (itemWidth > 10)
			{
				stepSize = 5.f;
			}
			else if (itemWidth > 4)
			{
				stepSize = 10.f;
			}
			else if (itemWidth > 1.5f)
			{
				stepSize = 25.f;
			}

			ImGui::SetCursorPos({ 0.f, 0.f });

			ImGui::Dummy({ 0, 0.0f });
			ImGui::Dummy({ 0, 0.0f });

			for (float textValue = 0; textValue <= start + endOffset; textValue += stepSize)
			{
				ImGui::SameLine();

				if (textValue >= start - 1)
				{
					float x = calculateX(textValue, start - 1);
					ImGui::SetCursorPosX(x + 8.f);
					drawDivider(x + 14.f);

					if (textValue >= workRangeStart && textValue <= workRangeEnd)
					{
						ImGui::Text("%.0f", textValue);
					}
					else
					{
						ImGui::TextDisabled("%.0f", textValue);
					}
				}
				else
				{
					ImGui::Dummy({ 0,0 });
				}
			}
			for (float textValue = 0; textValue >= start; textValue -= stepSize)
			{
				ImGui::SameLine();
				float x = calculateX(textValue, start);
				ImGui::SetCursorPosX(x);

				if (textValue == 0.f && stepSize != 1)
				{
					ImGui::Dummy({ 0,0 });
				}
				else
				{
					drawDivider(x + 14.f);

					if (textValue >= workRangeStart && textValue <= workRangeEnd)
					{
						ImGui::Text("%.0f", textValue);
					}
					else
					{
						ImGui::TextDisabled("%.0f", textValue);
					}
				}
			}
			DrawHorizontalLine(false, ImColor(0.7f, 0.7f, 0.7f), 6.f);
		}

		void drawPlayerControls()
		{
			ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2.f - 40.f);

			if (PlayBackButton("###ToStart", PlaybackType::GoToStart))
			{
				*sequencerInfo.currentFrame = sequencerInfo.startFrame;
			}
			ImGui::SameLine(0, 2.f);
			if (PlayBackButton("###PreviousTimeFrame", PlaybackType::GoBackKeyframe))
			{
				float currentFrame = *sequencerInfo.currentFrame;
				float jumpTo = sequencerInfo.startFrame;
				for (auto track : sequencerInfo.tracks)
				{
					if (track.max < currentFrame && track.max > jumpTo)
					{
						jumpTo = track.max;
					}
					else if (track.min < currentFrame && track.min > jumpTo)
					{
						jumpTo = track.min;
					}
					for (auto eventLine : track.eventInfo)
					{
						if (eventLine.max < currentFrame && eventLine.max > jumpTo)
						{
							jumpTo = eventLine.max;
						}
						else if (eventLine.min < currentFrame && eventLine.min > jumpTo)
						{
							jumpTo = eventLine.min;
						}
					}
				}
				*sequencerInfo.currentFrame = jumpTo;
			}
			ImGui::SameLine(0, 2.f);
			if (sequencerInfo.isPlaying)
			{
				if (PlayBackButton("##Stop", PlaybackType::Stop))
				{
					sequencerInfo.isPlaying = false;
				}
			}
			else
			{
				if (PlayBackButton("##Backward", PlaybackType::PlayReverse))
				{
					sequencerInfo.isPlaying = true;
					sequencerInfo.isPlayingForward = false;
				}
				ImGui::SameLine(0, 2.f);
				if (PlayBackButton("##Forward", PlaybackType::PlayForward))
				{
					sequencerInfo.isPlaying = true;
					sequencerInfo.isPlayingForward = true;
				}
			}
			ImGui::SameLine(0, 2.f);
			if (PlayBackButton("###NextTimeFrame", PlaybackType::GoForwardKeyframe))
			{
				float currentFrame = *sequencerInfo.currentFrame;
				float jumpTo = sequencerInfo.endFrame;
				for (auto track : sequencerInfo.tracks)
				{
					if (track.max > currentFrame && track.max < jumpTo)
					{
						jumpTo = track.max;
					}
					else if (track.min > currentFrame && track.min < jumpTo)
					{
						jumpTo = track.min;
					}
					for (auto eventLine : track.eventInfo)
					{
						if (eventLine.max > currentFrame && eventLine.max < jumpTo)
						{
							jumpTo = eventLine.max;
						}
						else if (eventLine.min > currentFrame && eventLine.min < jumpTo)
						{
							jumpTo = eventLine.min;
						}
					}
				}
				*sequencerInfo.currentFrame = jumpTo;
			}
			ImGui::SameLine(0, 2.f);
			if (PlayBackButton("###ToEnd", PlaybackType::GoToEnd))
			{
				*sequencerInfo.currentFrame = sequencerInfo.endFrame;
			}

			if (sequencerInfo.isPlaying)
			{
				if (sequencerInfo.isPlayingForward)
				{
					*sequencerInfo.currentFrame += ImGui::GetIO().DeltaTime;
					if (*sequencerInfo.currentFrame > sequencerInfo.endFrame)
					{
						*sequencerInfo.currentFrame = sequencerInfo.startFrame;
					}
				}
				else
				{
					*sequencerInfo.currentFrame -= ImGui::GetIO().DeltaTime;
					if (*sequencerInfo.currentFrame < sequencerInfo.startFrame)
					{
						*sequencerInfo.currentFrame = sequencerInfo.endFrame;
					}
				}
			}
		}

		bool PlayBackButton(const char* id, const PlaybackType& type)
		{
			ImVec2 size = { 24.f, 0 };
			if (type == PlaybackType::Stop)
			{
				size.x *= 2.f;
				size.x += 8.f;
			}
			auto pos = GetCursorPos();

			bool b = ImGui::Button(id, size);

			float x = 8.f;
			float y = 9.f;

			if (type == PlaybackType::GoToStart)
			{
				DrawBarShape({ pos.x + x, pos.y + y }, 6.f);
				DrawTriangleShape({ pos.x + x + 9.f, pos.y + y }, 6.f, true);
			}
			else if (type == PlaybackType::GoToEnd)
			{
				x += 2.f;
				DrawTriangleShape({ pos.x + x + 2.f, pos.y + y }, 6.f, false);
				DrawBarShape({ pos.x + x + 6.f, pos.y + y }, 6.f);
			}
			else if (type == PlaybackType::GoBackKeyframe)
			{
				DrawDiamondShape({ pos.x + x, pos.y + y }, 6.f);
				DrawTriangleShape({ pos.x + x + 12.f, pos.y + y }, 6.f, true);
			}
			else if (type == PlaybackType::GoForwardKeyframe)
			{
				x += 2.f;
				DrawTriangleShape({ pos.x + x , pos.y + y }, 6.f, false);
				DrawDiamondShape({ pos.x + x + 6.f, pos.y + y }, 6.f);
			}

			else if (type == PlaybackType::PlayReverse)
			{
				x += 6.f;
				DrawTriangleShape({ pos.x + x , pos.y + y }, 6.f, true);

			}
			else if (type == PlaybackType::PlayForward)
			{
				x += 8.f;
				DrawTriangleShape({ pos.x + x , pos.y + y }, 6.f, false);
			}
			else if (type == PlaybackType::Stop)
			{
				x += 16.f;
				DrawBarShape({ pos.x + x , pos.y + y }, 6);
				DrawBarShape({ pos.x + x + 8.f, pos.y + y }, 6);
			}
			return b;
		}

	};
	using namespace internal;

	bool EventLine(const char* id, float* start, float* end, float* startCap, float* endCap, const ImColor& trackColor)
	{
		startCap;
		endCap;

		float f = 0;
		float f2 = ImGui::GetWindowWidth();
		DrawTrackLine(f, f2, trackColor);

		ImGui::Dummy({ 4.f, 0.f });
		ImGui::SameLine();
		auto pos = GetCursorPos();
		pos.x += 4.f;
		pos.y += 8.f;
		ImGui::RenderBullet(ImGui::GetCurrentWindow()->DrawList, pos, ImColor(1,1,1).operator unsigned int());
		std::string name = "  ";
		name += id;
		ImGui::Text(name.c_str());
		ImGui::SameLine();
		std::string button = "e##";
		button += id;

		currentTrackWidth = GetLastCursorPosX() + 10.f;

		ImGui::SetCursorPosX(lastTrackWidth - 20.f);

		bool isClicked = ImGui::SmallButton(button.c_str());

		if (currentTrackWidth > sequencerInfo.accountTrackNameWidth)
		{
			sequencerInfo.accountTrackNameWidth = currentTrackWidth;
		}

		sequencerInfo.tracks[sequencerInfo.currentTrack].eventInfo.push_back({ std::string(id), *start, *end, trackColor });

		return isClicked;
	}

	bool BeginTrack(const char* id, float* trackStart, float* trackEnd, const ImColor& trackColor)
	{
		float f = 0;
		float f2 = ImGui::GetWindowWidth();
		DrawTrackLine(f, f2, trackColor);

		ImGui::Dummy({ 2.f, 0.f });
		ImGui::SameLine();
		ImGui::Text(id);
		ImGui::SameLine();
		ImGui::Dummy({ 10.f, 0.f });

		currentTrackWidth = GetLastCursorPosX();

		sequencerInfo.tracks.push_back({ std::string(id), *trackStart, *trackEnd, trackColor });

		return true;
	}

	void DrawTrack(const char* id, float& start, float& end, const float& min, const float& max, const ImColor& trackColor, bool small)
	{
		DrawTrack(id, start, end, min, max, min, max, trackColor, small);
	}

	void DrawTrack(const char* id, float& start, float& end, const float& startMin, const float& startMax, const float& endMin, const float& endMax, const ImColor& trackColor, bool small)
	{
		const float startX = calculateX(start, sequencerInfo.startFrame) + sequencerInfo.centerLineOffset;
		const float endX = calculateX(end, sequencerInfo.startFrame) + sequencerInfo.centerLineOffset;

		if (end > *sequencerInfo.timelineStart)
			DrawTrackLine(startX, endX, trackColor, small);
		if (start >= *sequencerInfo.timelineStart)
		{
			std::string _start = id;
			_start += "_start";
			DrawDiamond(_start.c_str(), start, startMin, startMax);
		}
		if (end >= *sequencerInfo.timelineStart)
		{
			std::string _end = id;
			_end += "_end";
			DrawDiamond(_end.c_str(), end, endMin, endMax);
		}
	}

	void EndTrack()
	{
		if (currentTrackWidth > sequencerInfo.accountTrackNameWidth)
		{
			sequencerInfo.accountTrackNameWidth = currentTrackWidth;
		}
		sequencerInfo.currentTrack++;
	}

	bool BeginSequencer(const char* id, const ImVec2& size_arg, float* currentFrame, float* startFrame, float* endFrame, float* timelineStartFrame, float* timelineEndOffset)
	{
		IM_ASSERT(sequencerInfo.inSequencer == false && "Cannot start another sequencer inside a sequencer");

		bool childOpen = ImGui::BeginChild(id, size_arg);
		if (!childOpen)
		{
			ImGui::EndChild();
			return childOpen;
		}

		sequencerInfo.timelineStart = timelineStartFrame;
		sequencerInfo.timelineEndOffset = timelineEndOffset;

		sequencerInfo.startFrame = *startFrame;
		sequencerInfo.endFrame = *endFrame;
		sequencerInfo.currentFrame = currentFrame;

		sequencerInfo.id = id;
		sequencerInfo.id += "_child";

		sequencerInfo.sizeArg = size_arg;

		if (size_arg.y == 0.f)
		{
			sequencerInfo.sizeArg.y = ImGui::GetWindowHeight() - 30.f;
		}
		else
		{
			sequencerInfo.sizeArg.y -= 30.f;
		}

		if (size_arg.x == 0.f)
		{
			sequencerInfo.sizeArg.x = ImGui::GetWindowWidth() - lastTrackWidth;
		}
		else
		{
			sequencerInfo.sizeArg.x -= lastTrackWidth;
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.f,0.f });
		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.f);
		sequencerInfo.trackInfoChildOpened = ImGui::BeginChild(sequencerInfo.id.c_str(), { lastTrackWidth, sequencerInfo.sizeArg.y });

		sequencerInfo.timelineSize = ImGui::GetWindowWidth();

		ImGui::NewLine();
		ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 2.f);
		sequencerInfo.trackInfoChildOpened |= ImGui::BeginChild(sequencerInfo.id.c_str(), { 0,0 });
		ImGui::PopStyleVar(3);

		ImGui::Dummy({ 0, 0.f });
		DrawHorizontalLine(true, ImColor(0.7f, 0.7f, 0.7f));
		sequencerInfo.inSequencer = true;
		return true;
	}

	void EndSequencer()
	{
		IM_ASSERT(sequencerInfo.inSequencer == true && "Calling EndSequencer before StartSequencer");
		sequencerInfo.inSequencer = false;

		if (sequencerInfo.trackInfoChildOpened)
		{
			lastTrackWidth = sequencerInfo.accountTrackNameWidth;
		}
		sequencerInfo.accountTrackNameWidth = 0.f;
		nextTrackOffset = 0.f;

		float scrollY = ImGui::GetScrollY();

		ImGui::EndChild();
		ImGui::EndChild();

		ImGui::SameLine(0, 0);
		sequencerInfo.id += "1";
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.f,0.f });
		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.f);
		ImGui::BeginChild(sequencerInfo.id.c_str(), { 0,sequencerInfo.sizeArg.y }, false, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

		sequencerInfo.timelineSize = ImGui::GetWindowWidth();

		drawTimeLine(*sequencerInfo.timelineStart, *sequencerInfo.timelineEndOffset, sequencerInfo.startFrame, sequencerInfo.endFrame);

		float point = *sequencerInfo.currentFrame;
		point = calculateX(point);
		if (*sequencerInfo.currentFrame > *sequencerInfo.timelineStart)
		{
			drawTrackerLine(point);
		}

		sequencerInfo.id += "1";

		ImGui::BeginChild(sequencerInfo.id.c_str(), { 0, 0.f }, false, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

		// TODO: set panning flag to prevent other input to also focus on panning, e.g camera panning when cursor moves outside ImGuiWindow.
		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Middle))
		{
			sequencerInfo.isPanningTimeline = true;
		}
		else if (ImGui::IsMouseDown(ImGuiMouseButton_Middle) && sequencerInfo.isPanningTimeline)
		{
			*sequencerInfo.timelineStart += ImGui::GetIO().MouseDelta.x;
		}
		else
		{
			sequencerInfo.isPanningTimeline = false;
		}

		ImGui::Dummy({ 0, 2.f });

		ImGui::SetScrollY(scrollY);

		scrollY = ImGui::GetIO().MouseWheel;

		if (scrollY && ImGui::IsWindowHovered())
		{
			*sequencerInfo.timelineStart += (scrollY * 10);
			*sequencerInfo.timelineEndOffset += (-scrollY * 20);

			if (*sequencerInfo.timelineEndOffset < 10.f)
			{
				*sequencerInfo.timelineEndOffset = 10.f;
			}
		}

		for (auto& track : sequencerInfo.tracks)
		{
			auto color = track.color;
			color.Value.w = 0.7f;
			DrawTrackLine(0, ImGui::GetWindowWidth() - 2.f, color);
			DrawTrack(track.name.c_str(), track.min, track.max, 0, sequencerInfo.endFrame, ImColor(200, 113, 0), true);
			ImGui::NewLine();
			for (auto& event : track.eventInfo)
			{
				color = event.color;
				color.Value.w = 0.7f;
				DrawTrackLine(0, ImGui::GetWindowWidth() - 2.f, color);
				DrawTrack(event.name.c_str(), event.min, event.max,
					track.min, event.max,
					event.min, track.max, ImColor(200, 113, 0), true);
				ImGui::NewLine();
			}
		}

		point = *sequencerInfo.currentFrame;
		point = calculateX(point);
		if (*sequencerInfo.currentFrame > *sequencerInfo.timelineStart)
		{
			ImGui::SetCursorPos({ 0,0 });
			drawTrackerLine(point);
		}
		ImGui::EndChild();
		ImGui::SetCursorPos({ 0, 0 });
		ImGui::Dummy({ 0,0 });
		drawTracker(*sequencerInfo.currentFrame);

		drawDivider(0);

		ImGui::EndChild();
		ImGui::PopStyleVar(2);

		DrawHorizontalLine(true, ImColor(0.7f, 0.7f, 0.7f));
		drawDivider(ImGui::GetWindowWidth() - 2.f, 2.f);
		drawPlayerControls();

		ImGui::EndChild();

		sequencerInfo.tracks.clear();
		sequencerInfo.currentTrack = 0;
	}
}
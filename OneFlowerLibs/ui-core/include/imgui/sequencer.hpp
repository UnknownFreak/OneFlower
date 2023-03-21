#pragma once

#include <string>
#include <imgui/imgui.h>

namespace of::imgui
{
	struct EventInfo
	{
		std::string name;
		float& min;
		float& max;
		const ImColor color;
	};

	struct TrackInfo
	{
		std::string name;
		float& min;
		float& max;
		const ImColor& color;

		ImVector<EventInfo> eventInfo;
	};

	struct InternalSequencerInfo
	{
		const float centerLineOffset = 14.f;
		bool inSequencer = false;
		float* timelineStart;
		float* timelineEndOffset;
		float startFrame;
		float endFrame;
		float* currentFrame;

		float accountTrackNameWidth = 0.f;
		float timelineSize;

		ImVector<TrackInfo> tracks;
		int currentTrack = 0;
		std::string id;
		ImVec2 sizeArg;

		bool trackInfoChildOpened = false;
		bool isTrackSliderPressed = false;
		bool isPanningTimeline = false;
		bool isPlaying = false;
		bool isPlayingForward = true;
	};

	enum class PlaybackType
	{
		GoToStart,
		GoBackKeyframe,
		PlayReverse,
		PlayForward,
		Stop,
		GoForwardKeyframe,
		GoToEnd,
	};

	namespace internal
	{
		bool SequencerAddTrack();
		bool AddEventLine(const char* id);

		void DrawHorizontalLine(const bool& addPadding, const ImColor& color, const float& padding = 0.f);
		void drawDivider(const float& dividerPos, const float& thickness = 1.f);
		void DrawTrackLine(const float& start, const float& end, const ImColor& color, bool small = false);
		void DrawDiamond(const char* id, float& x, const float& min, const float& max);
	
		void drawTrackerLine(float line);
		void drawTracker(float& trackerPoint);
		void drawTimeLine(const float start, const float& endOffset, const float& workRangeStart, const float& workRangeEnd);

		void drawPlayerControls();
		bool PlayBackButton(const char* id, const PlaybackType& type);
	}

	bool EventLine(const char* id, float* start, float* end, float* startCap, float* endCap, const ImColor& trackColor);

	bool BeginTrack(const char* id, float* trackStart, float* trackEnd, const ImColor& trackColor);
	void DrawTrack(const char* id, float& start, float& end, const float& startMin, const float& startMax, const float& endMin, const float& endMax, const ImColor& trackColor, bool small = false);
	void DrawTrack(const char* id, float& start, float& end, const float& min, const float& max, const ImColor& trackColor, bool small = false);
	void EndTrack();

	bool BeginSequencer(const char* id, const ImVec2& size_arg, float* currentFrame, float* startFrame, float* endFrame, float* timelineStartFrame, float* timelineEndOffset);
	void EndSequencer();
	
}
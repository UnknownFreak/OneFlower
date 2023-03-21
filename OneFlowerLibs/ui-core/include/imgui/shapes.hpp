#pragma once

#include <imgui/imgui.h>

namespace of::imgui
{
	void DrawDiamondShape(const ImVec2& pos, const float& size);
	void DrawTriangleShape(const ImVec2& pos, const float& size, const bool& faceLeft = false);
	void DrawBarShape(const ImVec2& pos, const float& size);
}
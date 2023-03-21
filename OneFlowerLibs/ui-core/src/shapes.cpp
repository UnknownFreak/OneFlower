#include <imgui/shapes.hpp>

namespace of::imgui
{
	void DrawDiamondShape(const ImVec2& pos, const float& size)
	{
		const float xPos = pos.x;
		const float yPos = pos.y;
		auto drawList = ImGui::GetWindowDrawList();
		drawList->PathLineTo({ xPos + size, yPos });
		drawList->PathLineTo({ xPos, yPos + size });
		drawList->PathLineTo({ xPos - size, yPos });
		drawList->PathLineTo({ xPos, yPos - size });
		drawList->PathLineTo({ xPos + size, yPos });
		drawList->PathFillConvex(ImColor(0.3f, 0.3f, 0.3f));
		drawList->PathLineTo({ xPos + size, yPos });
		drawList->PathLineTo({ xPos, yPos + size });
		drawList->PathLineTo({ xPos - size, yPos });
		drawList->PathLineTo({ xPos, yPos - size });
		drawList->PathLineTo({ xPos + size, yPos });
		drawList->PathStroke(ImColor(0.2f, 0.2f, 0.2f));
	}

	void DrawTriangleShape(const ImVec2& pos, const float& size, const bool& faceLeft)
	{
		const float xPos = pos.x;
		const float yPos = pos.y;
		auto drawList = ImGui::GetWindowDrawList();
		if (faceLeft)
		{
			drawList->PathLineTo({ xPos, yPos + size });
			drawList->PathLineTo({ xPos - size, yPos });
			drawList->PathLineTo({ xPos, yPos - size });
			drawList->PathLineTo({ xPos, yPos + size });
			drawList->PathFillConvex(ImColor(0.3f, 0.3f, 0.3f));
			drawList->PathLineTo({ xPos, yPos + size });
			drawList->PathLineTo({ xPos - size, yPos });
			drawList->PathLineTo({ xPos, yPos - size });
			drawList->PathLineTo({ xPos, yPos + size });
			drawList->PathStroke(ImColor(0.2f, 0.2f, 0.2f));
		}
		else
		{
			drawList->PathLineTo({ xPos - size, yPos + size });
			drawList->PathLineTo({ xPos, yPos });
			drawList->PathLineTo({ xPos - size, yPos - size });
			drawList->PathLineTo({ xPos - size, yPos + size });
			drawList->PathFillConvex(ImColor(0.3f, 0.3f, 0.3f));
			drawList->PathLineTo({ xPos - size, yPos + size });
			drawList->PathLineTo({ xPos, yPos });
			drawList->PathLineTo({ xPos - size, yPos - size });
			drawList->PathLineTo({ xPos - size, yPos + size });
			drawList->PathStroke(ImColor(0.2f, 0.2f, 0.2f));
		}
	}

	void DrawBarShape(const ImVec2& pos, const float& size)
	{
		const float xPos = pos.x;
		const float yPos = pos.y;
		auto drawList = ImGui::GetWindowDrawList();
		drawList->AddRectFilled({ xPos - 2.f, yPos - size }, { xPos + 2.f, yPos + size }, ImColor(0.3f, 0.3f, 0.3f));
		drawList->AddRect({ xPos - 2.f, yPos - size }, { xPos + 2.f, yPos + size }, ImColor(0.2f, 0.2f, 0.2f));
	}
}

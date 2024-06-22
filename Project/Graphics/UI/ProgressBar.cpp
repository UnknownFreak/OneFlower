#include "ProgressBar.hpp"
#include <utils/common/string.hpp>


Graphics::UI::ProgressBar::ProgressBar(const float& x, const float& y, const float& sizeX, const float& sizeY, const float& maxVal, const float& currentVal, const glm::vec3& color,
	const float& extensionTop, const float& extensionBottom, const bool& drawText, const float& textOffsetX, const float& textOffsetY) :
	x(x), y(y), sizeX(sizeX), sizeY(sizeY), maxVal(maxVal), currentVal(currentVal), UIContext(swizzle::input::Keys::KeyNone, "ProgressBar", true), extensionBottom(extensionBottom), extensionTop(extensionTop), drawText(drawText), textOffsetX(textOffsetX), textOffsetY(textOffsetY)
{
	color;
}

void Graphics::UI::ProgressBar::readInput()
{
}

void Graphics::UI::ProgressBar::setNewMax(const float& newMax)
{
	maxVal = newMax;
	update();
}

void Graphics::UI::ProgressBar::update(const float& newVal)
{
	currentVal = newVal;
	valueText = of::common::to_string_with_precision(currentVal, 0);
	update();
}

void Graphics::UI::ProgressBar::update()
{
	frac = currentVal / maxVal;
	if (frac > 1.f)
		frac = 1.f;
	if (frac < 0.f)
		frac = 0.f;
	//points[4].position = { x + 1.f , y + 1.f};
	//points[5].position = { x + 1.f , y + sizeY};
	//points[6].position = { x + ((sizeX + extensionBottom) * frac) , y + sizeY };
	//points[7].position = { x + ((sizeX + extensionTop) * frac) , y + 1.f};
	//theBar.update(points);
	//if (drawText)
	//{
	//	auto lb = valueText.getLocalBounds();
	//	valueText.setPosition(std::floor(x + textOffsetX) , std::floor(y + textOffsetY));
	//}
	tooltip.setToolTip(of::common::to_string_with_precision(currentVal, 0) + "/" + of::common::to_string_with_precision(maxVal, 0));
}

void Graphics::UI::ProgressBar::render()
{
	if (visible)
	{
		ImGui::ProgressBar(frac, ImVec2(sizeX, sizeY));
		if(ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted("foo");
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
}

//void Graphics::UI::ProgressBar::drawToolTip(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	target.draw(tooltip, states);
//}

void Graphics::UI::ProgressBar::onMouseHover(const glm::vec2& mouse)
{
	tooltip.drawToolTip = visible;
	if (tooltip.drawToolTip && mouseInside({ x,y }, { sizeX + extensionTop, sizeY }, mouse))
	{
		tooltip.setPosition(mouse);
	}
}

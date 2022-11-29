#ifndef ProgressBar_HPP
#define ProgressBar_HPP

#include "UIContext.hpp"
#include "PlainToolTip.hpp"

#include <glm/vec3.hpp>

namespace Graphics::UI
{
	class ProgressBar : public UIContext
	{
		float frac = 0;
		PlainToolTip tooltip;
		float x, y, sizeX, sizeY;
		float extensionTop, extensionBottom;
		float textOffsetX, textOffsetY;
		float maxVal, currentVal;
		of::common::String valueText;
		bool drawText;
	protected:

	public:
		ProgressBar(const float& x, const float& y, const float& sizeX, const float& sizeY, const float& max, const float& current, const glm::vec3& color,
			const float& extensionTop, const float& extensionBottom, const bool& drawText=true, const float& textOffsetX=0.f, const float& textOffsetY=0.f);

		// Inherited via UIContext
		virtual void readInput() override;
		void setNewMax(const float& newMax);
		void update(const float& currentVal);
		virtual void update() override;
		virtual void render() override;

		// Inherited via UIContext
		virtual void onMouseHover(const glm::vec2& mouse) override;
	};
}

#endif
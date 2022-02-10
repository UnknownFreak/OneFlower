#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <Helpers/Rect.hpp>

#include <vector>

struct Renderable : public sf::Drawable
{
	virtual ~Renderable() = default;
	Renderable(const Core::Rect<float>& box) : drawBox(box) {}
	Renderable(const Renderable& copy) : Renderable(copy.drawBox) {}
	Core::Rect<float> drawBox;
	Core::Rect<float> swapBox;

	virtual void setTransparency(const bool& ) {}
};
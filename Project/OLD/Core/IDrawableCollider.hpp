#ifndef IDrawableCollider_HPP
#define IDrawableCollider_HPP

#include "ICollider.hpp"

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

template <class T>
class IDrawableCollider : public sf::Drawable, public ICollider<T>
{

public:

	inline IDrawableCollider(float& x, float& y, float& w, float& h) : ICollider(x, y, w, h)
	{
	}

	inline IDrawableCollider(const IDrawableCollider& copy) : ICollider(copy)
	{
	}

	inline IDrawableCollider& operator=(const IDrawableCollider& left) = delete;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

};




#endif
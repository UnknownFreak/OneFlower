#ifndef ICOLLIDER_HPP
#define ICOLLIDER_HPP

#include <Core\Vector.h>
#include <Core\Rect.hpp>

template <class T>
class QuadTreeNode;

template<class T>
class ICollider
{

public:
	QuadTreeNode<T>* node;
	bool update;
	Core::Rect<float&> rect;

	inline ICollider(float& x=0, float& y=0, float& w=0, float& h=0) : rect(x, y, w, h), update(false), node(nullptr)
	{
	}

	inline ICollider(const ICollider& copy) : rect(copy.rect), update(copy.update), node(copy.node)
	{
	}

	inline ICollider& operator=(const ICollider& left) = delete;

	inline bool collides(const Core::FloatRect& other) const
	{
		float x=other.x, y=other.y, w=other.w, h=other.h;
		return rect.intersects(Core::Rect<float&>(x, y, w, h));
	}
	inline bool collides(const Core::Rect<float&>& other) const
	{
		return rect.intersects(other);
	}
	inline bool collides(const Core::Vector2& other) const
	{
		return rect.intersects(Core::Rect<float&>(other.x, other.y, 1.f, 1.f));
	}
	inline bool collides(const ICollider* other) const
	{
		return rect.intersects(other->rect);
	}

	inline bool needUpdate() const {
		return update;
	}
	
	virtual void Update() {
	}
};

#endif 
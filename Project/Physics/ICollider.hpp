#ifndef ICOLLIDER_HPP
#define ICOLLIDER_HPP

#include <Core\Vector.h>
#include <Core\Rect.hpp>
#include "Collider.hpp"

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

class QuadTreeNode;
namespace Physics
{
	class ICollider : public sf::Drawable, public Collider
	{

	public:

		enum class ColliderType
		{
			Box,
			Poly
		};

		QuadTreeNode* node;
		bool update;
		Core::Rect<float&> rect;
		ColliderType colliderType;

		inline ICollider(float& x, float& y, float& w, float& h) : rect(x, y, w, h), update(false), node(nullptr), colliderType(ColliderType::Box)
		{
		}

		inline ICollider(const ICollider& copy) : rect(copy.rect), update(copy.update), node(copy.node), colliderType(ColliderType::Box)
		{
		}

		inline ICollider& operator=(const ICollider& left) = delete;

		virtual inline bool collides(const Core::FloatRect& other) const
		{
			float x=other.x, y=other.y, w=other.w, h=other.h;
			return rect.intersects(Core::Rect<float&>(x, y, w, h));
		}
		virtual inline bool collides(const Core::Rect<float&>& other) const
		{
			return rect.intersects(other);
		}
		virtual inline bool collides(const Core::Vector2& other) const
		{
			float x = other.x, y=other.y, one = 1.f;
			return rect.intersects(Core::Rect<float&>(x, y, one, one));
		}
		virtual inline bool collides(const ICollider& other) const
		{
			return rect.intersects(other.rect);
		}

		inline virtual bool needUpdate() {
			return update;
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {};
	};
}

#endif 
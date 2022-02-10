#include "ICollider.hpp"
#include <Helpers/Vector.hpp>
#include <Module/Globals.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

namespace Interfaces {

	sf::ConvexShape ICollider::fromBox(const float& x, const float& y, const float& x2, const float& y2)
	{
		sf::ConvexShape cc = sf::ConvexShape(4);

		cc.setPoint(0, sf::Vector2f(x, y));
		cc.setPoint(1, sf::Vector2f(x2, y));
		cc.setPoint(2, sf::Vector2f(x2, y2));
		cc.setPoint(3, sf::Vector2f(x, y2));
		return cc;
	}

	sf::ConvexShape transform(const sf::ConvexShape& shape)
	{
		sf::ConvexShape s;
		s.setPointCount(shape.getPointCount());
		s.setFillColor(shape.getFillColor());
		s.setOutlineColor(shape.getOutlineColor());
		s.setOutlineThickness(shape.getOutlineThickness());
		auto transform = shape.getTransform();
		for (size_t p = 0; p < shape.getPointCount(); p++)
			s.setPoint(p, transform.transformPoint(shape.getPoint(p)));
		return s;
	}

	int orientation(const Core::Vector2f& p, const Core::Vector2f& q, const Core::Vector2f& r)
	{
		const auto val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

		return val > 0.f ? 1 : 2; // clock or counterclock wise
	}

	bool doIntersect(const Core::Vector2f& p1, const Core::Vector2f& q1, const Core::Vector2f& p2, const Core::Vector2f& q2)
	{
		const auto o1 = orientation(p1, q1, p2);
		const auto o2 = orientation(p1, q1, q2);
		const auto o3 = orientation(p2, q2, p1);
		const auto o4 = orientation(p2, q2, q1);

		return o1 != o2 && o3 != o4;
	}

	std::tuple<Core::Vector2f, bool> ICollider::intersect(const sf::ConvexShape& r1, const Core::Vector2f& aCenter, const sf::ConvexShape& r2, const Core::Vector2& bCenter) const
	{
		sf::ConvexShape poly1 = transform(r1);
		sf::ConvexShape poly2 = transform(r2);

		float overlap = INFINITY;
		Core::Vector2f collisionEdgeNormal{ 0.f, 0.f };

		for (int shape = 0; shape < 2; shape++)
		{
			if (shape == 1)
			{
				poly1 = transform(r2);
				poly2 = transform(r1);
			}

			for (size_t a = 0; a < poly1.getPointCount(); a++)
			{
				size_t b = (a + 1) % poly1.getPointCount();

				auto pt = poly1.getPoint(a);
				auto pt2 = poly1.getPoint(b);

				if (doIntersect(aCenter, bCenter, { pt.x, pt.y }, { pt2.x, pt2.y }))
				{
					collisionEdgeNormal = { pt.x - pt2.x, pt.y - pt2.y };
				}

				Core::Vector2f axisProj = { -(poly1.getPoint(b).y - poly1.getPoint(a).y), poly1.getPoint(b).x - poly1.getPoint(a).x };

				// Optional normalisation of projection axis enhances stability slightly
				float d = sqrtf(axisProj.x * axisProj.x + axisProj.y * axisProj.y);
				axisProj = { axisProj.x / d, axisProj.y / d };

				// Work out min and max 1D points for r1
				float min_r1 = INFINITY, max_r1 = -INFINITY;
				for (size_t p = 0; p < poly1.getPointCount(); p++)
				{
					float q = (poly1.getPoint(p).x * axisProj.x + poly1.getPoint(p).y * axisProj.y);
					min_r1 = std::min(min_r1, q);
					max_r1 = std::max(max_r1, q);
				}

				// Work out min and max 1D points for r2
				float min_r2 = INFINITY, max_r2 = -INFINITY;
				for (size_t p = 0; p < poly2.getPointCount(); p++)
				{
					float q = (poly2.getPoint(p).x * axisProj.x + poly2.getPoint(p).y * axisProj.y);
					min_r2 = std::min(min_r2, q);
					max_r2 = std::max(max_r2, q);
				}

				// Calculate actual overlap along projected axis, and store the minimum
				overlap = std::min(std::min(max_r1, max_r2) - std::max(min_r1, min_r2), overlap);

				if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
					return { {0,0}, false };
			}
		}
		

		// If we got here, the objects have collided, we will displace r1
		// by overlap along the vector between the two object centers
		collisionEdgeNormal = collisionEdgeNormal.lnormal();
		collisionEdgeNormal.normalize();
		collisionEdgeNormal.abs();
		
		auto dd = r2.getPosition() - r1.getPosition();

		Core::Vector2f o{ overlap * dd.x / std::fabs(dd.x), overlap * dd.y / std::fabs(dd.y) };
		return { o * collisionEdgeNormal, true };
	}

	bool ICollider::within(const float& other, const float& margin) const
	{
		return within(other, margin, margin);
	}

	bool ICollider::within(const float& other, const float& lower, const float& upper) const
	{
		const auto up = other + upper;
		const auto lo = other - lower;
		return (lo < position->z) && (position->z < up);
	}

	ICollider::ICollider(Core::Vector3f* pos, float size_x, float size_y, Enums::ColliderAlgorithm algo, Enums::ColliderType type) : collider{ 0.f, 0.f, size_x, size_y }, position(pos),
		algorithm(algo), colliderType(type), requireUpdate(true), convexCollider(fromBox(0.f, 0.f, size_x, size_y)),
		drawColliders(Engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX]), Renderable({ 0.f, 0.f, size_x, size_y })
	{
		convexCollider.setFillColor(sf::Color::Transparent);
		convexCollider.setOutlineColor(sf::Color::Cyan);
		convexCollider.setOutlineThickness(2);
		convexCollider.setOrigin(size_x/2, size_y/2);

		s.setRadius(2.f);
		s.setFillColor(sf::Color::Magenta);
	}

	ICollider::ICollider(const ICollider& copy) : ICollider(copy.position, copy.collider.w, copy.collider.h, copy.algorithm, copy.colliderType)
	{
		requireUpdate = copy.requireUpdate;
	}

	ICollider& ICollider::operator=(const ICollider& right)
	{
		position = right.position;
		collider = right.collider;
		colliderType = right.colliderType;
		algorithm = right.algorithm;
		requireUpdate = right.requireUpdate;
		convexCollider = right.convexCollider;
		drawBox = collider;
		return *this;
	}

	bool ICollider::Collides(Core::Vector2& other) const
	{
		return convexCollider.getGlobalBounds().intersects(sf::Rect<float>(other.x, other.y, 1.f, 1.f));
	}

	bool ICollider::Collides(Core::FloatRect& other) const
	{
		return convexCollider.getGlobalBounds().intersects(other.toSFRect());
	}

	bool ICollider::Collides(const Core::FloatRect& other) const
	{
		return convexCollider.getGlobalBounds().intersects(other.toSFRect());
	}

	std::tuple<Core::Vector2f, bool> ICollider::Collides(ICollider* other)
	{
		if (within(other->position->z, 0.1f, 0.9f) && colliderType != Enums::ColliderType::Void && other->colliderType != Enums::ColliderType::Void)
			if (algorithm == Enums::ColliderAlgorithm::Square)
				return {
					{0,0},
					convexCollider.getGlobalBounds().intersects(other->convexCollider.getGlobalBounds()) };
			else
				return intersect(convexCollider, collider.getCenter(), ((ICollider*)other)->convexCollider, other->collider.getCenter());
		return { {0,0}, false };
	}

	void ICollider::updateColliderPos(const Core::Vector2f& pos, const float& extra_offset)
	{
		collider.pos = { pos.x, pos.y - extra_offset };
		//convexCollider.setPosition(pos.x, pos.y);
		convexCollider.setPosition(collider.getCenter().x, collider.getCenter().y);
		//drawBox.pos = { pos.x, pos.y - extra_offset + (z * Globals::Z_OFFSET )};
		drawBox.pos = { pos.x, pos.y - extra_offset};
		s.setPosition(convexCollider.getPosition().x, convexCollider.getPosition().y);

	}

	Core::FloatRect ICollider::getBox() const
	{
		return collider;
	}

	void ICollider::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (drawColliders)
		{
			std::stringstream stream;
			stream << std::fixed << std::setprecision(1) << position->z;
			std::string st = stream.str();
			sf::Text t(sf::String(st), Globals::font, 16);
			//sf::ConvexShape css = convexCollider;
			sf::ConvexShape css = transform(convexCollider);
			//css.setPosition(convexCollider.getPosition().x, convexCollider.getPosition().y + (z * Globals::Z_OFFSET));
			t.setFillColor(sf::Color::Black);
			t.setPosition(convexCollider.getPosition().x, convexCollider.getPosition().y + (position->z * Globals::Z_OFFSET));

			sf::RectangleShape rs;
			rs.setFillColor(sf::Color::Transparent);
			rs.setOutlineColor(sf::Color::Black);
			rs.setOutlineThickness(1.f);
			rs.setPosition({ drawBox.x, drawBox.y });
			rs.setSize({ drawBox.w, drawBox.h });

			target.draw(css, states);
			target.draw(rs, states);
			target.draw(t, states);
			target.draw(s, states);
		}
	}
}

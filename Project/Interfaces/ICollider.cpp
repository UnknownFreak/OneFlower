#include "ICollider.hpp"
#include <Module/Globals.hpp>

#if defined max
#undef max
#endif

#if defined min
#undef min
#endif

namespace Interfaces {

	std::vector<glm::vec2> ICollider::fromBox(const float& x, const float& y, const float& x2, const float& y2)
	{
		std::vector<glm::vec2> v;

		v.push_back(glm::vec2(x, y));
		v.push_back(glm::vec2(x2, y));
		v.push_back(glm::vec2(x2, y2));
		v.push_back(glm::vec2(x, y2));
		return v;
	}

	std::vector<glm::vec2> transform(const std::vector<glm::vec2>& shape, const glm::vec2& center)
	{
		std::vector<glm::vec2> s;
		
		for (auto& p : shape)
		{
			s.push_back(p + center);
		}
		//auto transform = shape.getTransform();
		//for (size_t p = 0; p < shape.getPointCount(); p++)
		//	s.setPoint(p, transform.transformPoint(shape.getPoint(p)));
		return s;
	}

	int orientation(const glm::vec2& p, const glm::vec2& q, const glm::vec2& r)
	{
		const auto val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

		return val > 0.f ? 1 : 2; // clock or counterclock wise
	}

	bool doIntersect(const glm::vec2& p1, const glm::vec2& q1, const glm::vec2& p2, const glm::vec2& q2)
	{
		const auto o1 = orientation(p1, q1, p2);
		const auto o2 = orientation(p1, q1, q2);
		const auto o3 = orientation(p2, q2, p1);
		const auto o4 = orientation(p2, q2, q1);

		return o1 != o2 && o3 != o4;
	}

	std::tuple<glm::vec2, bool> ICollider::intersect(const std::vector<glm::vec2>& r1, const glm::vec2& aCenter, const std::vector<glm::vec2>& r2, const glm::vec2& bCenter) const
	{
		std::vector<glm::vec2> poly1 = transform(r1, { aCenter.x, aCenter.y });
		std::vector<glm::vec2> poly2 = transform(r2, { bCenter.x, bCenter.y });

		float overlap = INFINITY;
		glm::vec2 collisionEdgeNormal{ 0.f, 0.f };

		for (int shape = 0; shape < 2; shape++)
		{
			if (shape == 1)
			{
				poly1 = transform(r2, { bCenter.x, bCenter.y });
				poly2 = transform(r1, { aCenter.x, aCenter.y });
			}

			for (size_t a = 0; a < poly1.size(); a++)
			{
				size_t b = (a + 1) % poly1.size();

				auto pt = poly1[a];
				auto pt2 = poly1[b];

				if (doIntersect(aCenter, bCenter, { pt.x, pt.y }, { pt2.x, pt2.y }))
				{
					collisionEdgeNormal = { pt.x - pt2.x, pt.y - pt2.y };
				}

				glm::vec2 axisProj = { -(poly1[b].y - poly1[a].y), poly1[b].x - poly1[a].x };

				// Optional normalisation of projection axis enhances stability slightly
				float d = sqrtf(axisProj.x * axisProj.x + axisProj.y * axisProj.y);
				axisProj = { axisProj.x / d, axisProj.y / d };

				// Work out min and max 1D points for r1
				float min_r1 = INFINITY, max_r1 = -INFINITY;
				for (size_t p = 0; p < poly1.size(); p++)
				{
					float q = (poly1[p].x * axisProj.x + poly1[p].y * axisProj.y);
					min_r1 = std::min(min_r1, q);
					max_r1 = std::max(max_r1, q);
				}

				// Work out min and max 1D points for r2
				float min_r2 = INFINITY, max_r2 = -INFINITY;
				for (size_t p = 0; p < poly2.size(); p++)
				{
					float q = (poly2[p].x * axisProj.x + poly2[p].y * axisProj.y);
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
		collisionEdgeNormal = {-collisionEdgeNormal.y, collisionEdgeNormal.x};
		collisionEdgeNormal = (glm::vec2)glm::normalize(collisionEdgeNormal);
		glm::abs(collisionEdgeNormal);
		
		auto dd = bCenter - aCenter;

		glm::vec2 o{ overlap * dd.x / std::fabs(dd.x), overlap * dd.y / std::fabs(dd.y) };
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

	ICollider::ICollider(glm::vec3* pos, float size_x, float size_y, Enums::ColliderAlgorithm algo, Enums::ColliderType type) : collider{ glm::vec2{0.f, 0.f}, glm::vec2{size_x, size_y } }, position(pos),
		algorithm(algo), colliderType(type), requireUpdate(true), convexCollider(fromBox(0.f, 0.f, size_x, size_y)),
		drawColliders(Engine::GetModule<Globals>().boolGlobals[Globals::GLOBAL_DRAW_HITBOX])
	{
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
		return *this;
	}

	std::tuple<glm::vec2, bool> ICollider::Collides(ICollider* other)
	{
		if (within(other->position->z, 0.1f, 0.9f) && colliderType != Enums::ColliderType::Void && other->colliderType != Enums::ColliderType::Void)
			return intersect(convexCollider, collider.getCenter(), ((ICollider*)other)->convexCollider, other->collider.getCenter());
		return { {0,0}, false };
	}

	void ICollider::updateColliderPos(const glm::vec3& pos, const float& extra_offset)
	{
		collider.pos = { pos.x, pos.y - extra_offset};
		//convexCollider.setPosition(collider.getCenter().x, collider.getCenter().y);

	}

	Core::FloatRect ICollider::getBox() const
	{
		return collider;
	}
}

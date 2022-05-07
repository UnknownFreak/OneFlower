#ifndef ICollider_HPP
#define ICollider_HPP

#include <glm/glm.hpp>

#include <Helpers/Vector.hpp>
#include <Helpers/Vector3.hpp>
#include <Helpers/Rect.hpp>
#include <Helpers/Enum/ColliderType.hpp>

namespace Interfaces {
	class ICollider
	{
	public:
		Core::Vector3f* position;
	private:
		std::vector<glm::vec2> fromBox(const float& x1, const float& y1, const float& x2, const float& y2);
	protected:
		const bool& drawColliders;
		std::tuple<Core::Vector2f, bool> intersect(const std::vector<glm::vec2>& a, const Core::Vector2f& aCenter, const std::vector<glm::vec2>& b, const Core::Vector2& bCenter) const;

		bool within(const float& other, const float& margin) const;
		bool within(const float& other, const float& lower, const float& upper) const;

		bool isAttached = false;;
	public:

		bool requireUpdate;
		bool isRoof = false;

		ICollider(Core::Vector3f* pos, float size_x, float size_y, Enums::ColliderAlgorithm algo = Enums::ColliderAlgorithm::Square, Enums::ColliderType type = Enums::ColliderType::Void);
		ICollider(const ICollider& copy);
		ICollider& operator=(const ICollider& right);
		virtual ~ICollider() = default;
	
		virtual std::tuple<Core::Vector2f, bool> Collides(ICollider* other);
		virtual void doParentSimulate(const float& fElapsedTime) = 0;

		void updateColliderPos(const Core::Vector2f& pos, const float& extra_offset);

		Enums::ColliderAlgorithm algorithm;
		Enums::ColliderType colliderType;
	
		Core::FloatRect collider;
		std::vector<glm::vec2> convexCollider;

		inline bool needUpdate() {
			return requireUpdate;
		}

		virtual bool isActive() const { return false; };

		inline virtual void postUpdate() {};

		Core::FloatRect getBox() const;

		// Inherited via Drawable

		template <class Archive>
		void save(Archive& saver) const
		{
			saver(algorithm);
			saver(colliderType);
			saver(collider);
			saver(isRoof);
			const size_t count = convexCollider.getPointCount();
			saver(count);
			for (size_t i = 0; i < count; i++)
			{
				auto vec = convexCollider.getPoint(count);
				saver(vec.x, vec.y)
			}
		}

		template <class Archive>
		void load(Archive& loader)
		{
			loader(algorithm);
			loader(colliderType);
			loader(collider);
			loader(isRoof);
			const size_t count;
			loader(count);
			convexCollider.setPointCount(count);
			for (size_t i = 0; i < count; i++)
			{
				sf::Vector2f vec;
				loader(vec.x, vec.y);
				convexCollider.setPoint(count, vec);
			}
		}
	};
}

#endif
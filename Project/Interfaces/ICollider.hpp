#ifndef ICollider_HPP
#define ICollider_HPP

#include <Graphics/Renderable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <Helpers/Vector.hpp>
#include <Helpers/Vector3.hpp>
#include <Helpers/Rect.hpp>
#include <Helpers/Enum/ColliderType.hpp>

namespace Interfaces {
	class ICollider : public Renderable
	{
	public:
		Core::Vector3f* position;
		sf::CircleShape s;
	private:
		sf::ConvexShape fromBox(const float& x1, const float& y1, const float& x2, const float& y2);
	protected:
		const bool& drawColliders;
		std::tuple<Core::Vector2f, bool> intersect(const sf::ConvexShape& a, const Core::Vector2f& aCenter, const sf::ConvexShape& b, const Core::Vector2& bCenter) const;

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
	
		virtual bool Collides(Core::Vector2& other) const;
		virtual bool Collides(Core::FloatRect& other) const;
		virtual bool Collides(const Core::FloatRect& other) const;
		virtual std::tuple<Core::Vector2f, bool> Collides(ICollider* other);
		virtual void doParentSimulate(const float& fElapsedTime) = 0;

		void updateColliderPos(const Core::Vector2f& pos, const float& extra_offset);

		Enums::ColliderAlgorithm algorithm;
		Enums::ColliderType colliderType;
	
		Core::FloatRect collider;
		sf::ConvexShape convexCollider;

		inline bool needUpdate() {
			return requireUpdate;
		}

		inline virtual void postUpdate() {};

		Core::FloatRect getBox() const;

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

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
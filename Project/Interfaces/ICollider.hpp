#ifndef ICollider_HPP
#define ICollider_HPP

#include <vector>

#include <glm/glm.hpp>
#include <Helpers/Rect.hpp>
#include <Helpers/Enum/ColliderType.hpp>

namespace Interfaces {
	class ICollider
	{
	public:
		glm::vec3* position;
	private:
		std::vector<glm::vec2> fromBox(const float& x1, const float& y1, const float& x2, const float& y2);
	protected:
		const bool& drawColliders;
		std::tuple<glm::vec2, bool> intersect(const std::vector<glm::vec2>& a, const glm::vec2& aCenter, const std::vector<glm::vec2>& b, const glm::vec2& bCenter) const;

		bool within(const float& other, const float& margin) const;
		bool within(const float& other, const float& lower, const float& upper) const;

		bool isAttached = false;;
	public:

		bool requireUpdate;
		bool isRoof = false;

		ICollider(glm::vec3* pos, float size_x, float size_y, Enums::ColliderAlgorithm algo = Enums::ColliderAlgorithm::Square, Enums::ColliderType type = Enums::ColliderType::Void);
		ICollider(const ICollider& copy);
		ICollider& operator=(const ICollider& right);
		virtual ~ICollider() = default;
	
		virtual std::tuple<glm::vec2, bool> Collides(ICollider* other);
		virtual void doParentSimulate(const float& fElapsedTime) = 0;

		void updateColliderPos(const glm::vec3& pos, const float& extra_offset);

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
			const size_t count = convexCollider.size();
			saver(count);
			for (size_t i = 0; i < count; i++)
			{
				auto vec = convexCollider[i];
				saver(vec.x, vec.y);
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
			for (size_t i = 0; i < count; i++)
			{
				glm::vec2 vec;
				loader(vec.x, vec.y);
				convexCollider.push_back(vec);
			}
		}
	};
}

#endif
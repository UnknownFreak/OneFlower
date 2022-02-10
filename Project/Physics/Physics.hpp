#ifndef Physics_HPP
#define Physics_HPP

#include <Interfaces/IEngineModule.hpp>

#include <Interfaces/ICollider.hpp>
#include <unordered_set>
#include "QuadTree.hpp"
#include <mutex>

class GameObject;

namespace Physics
{
	struct BoxInfo
	{
		size_t id;
		Interfaces::ICollider* ptr;
		Core::FloatRect rect;
		Enums::ColliderType colliderType;
		bool operator==(const BoxInfo& b) const {
			return id == b.id;
		}

		bool needUpdate()
		{
			if (ptr)
				return ptr->needUpdate();
			return false;
		}
	};
	inline auto getBox = [](const BoxInfo& node)
	{
		return node.rect;
	};
	class PhysicsEngine : public Interfaces::IEngineResource<PhysicsEngine>
	{
		std::mutex mtx;
		std::vector<GameObject*> renderables;
		float elapsedTimeInternal;
		void runQuery(const Core::FloatRect& box);

		quadtree::Quadtree<BoxInfo, decltype(getBox)> qt;
	public:
		Core::Rect<float>& renderBox;

		PhysicsEngine();
		PhysicsEngine(const PhysicsEngine& copy);
		~PhysicsEngine() {}

		void update(const float& fElapsedTime);
		void addCollider(Interfaces::ICollider* collider);
		void updateCollider(Interfaces::ICollider* collider, Interfaces::ICollider* newCollider, const Core::FloatRect& oldBox);
		void removeCollider(Interfaces::ICollider* collider);

		Enums::EngineResourceType& getType() const
		{
			return type;
		}
	};
}

#endif
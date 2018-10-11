#ifndef HitboxComponent_HPP
#define HitboxComponent_HPP
#include "../ICollider.hpp"

#include <vector>
#include <Core\Rect.hpp>
#include <Core\Component\IBaseComponent.hpp>
#include <Core\Component\TransformComponent.hpp>
#include <Core\Component\GameObject.h>
namespace Component
{
	class HitboxComponent : public IBaseComponent < HitboxComponent >, public Physics::ICollider
	{
	public:

		inline virtual bool needUpdate() override {
			if (attachedOn)
			{
				Transform* tc = attachedOn->GetComponent<Transform>();
				bool need_update = tc->position != Core::Vector2(bounding.x, bounding.y);
				bounding.x = tc->position.x;
				bounding.y = tc->position.y;
				return need_update;
			}
			return false;
		}

		HitboxComponent();
		HitboxComponent(const HitboxComponent &hc);
		HitboxComponent(float x, float y, float w, float h);
		//LOW: Make a Render and Transform constructor ??
		~HitboxComponent();

		void registerCollisionCheck(Base* component);

		Core::FloatRect bounding;

		std::vector<Base*> collisionCall;

		virtual HitboxComponent* copy() const;
	
		template <class Archive>
		void serialize(Archive &ar)
		{
			ar(bounding.x);
			ar(bounding.y);
			ar(bounding.w);
			ar(bounding.h);
		}
	protected:
		void attachOn(GameObject* go);

	private:
		//sf::Rect<int> box;

		//template <class Archive>
		//void save(Archive &ar, const HitboxComponent &hc);
		//template <class Archive>
		//void load(Archive &ar, HitboxComponent &hc);
	};
}
#endif
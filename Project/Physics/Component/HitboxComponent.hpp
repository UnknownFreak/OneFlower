#ifndef HitboxComponent_HPP
#define HitboxComponent_HPP
//#include <SFML\Graphics\Rect.hpp>
#include <vector>
#include "../BoundingBox.hpp"
#include <Core\Component\IBaseComponent.hpp>
namespace Component
{
	class HitboxComponent :public IBaseComponent < HitboxComponent >
	{
	public:
		HitboxComponent();
		HitboxComponent(const HitboxComponent &hc);
		HitboxComponent(float x, float y, int w, int h);

		//LOW: Make a Render and Transform constructor ??
		~HitboxComponent();

		void registerCollisionCheck(BaseComponent* component);

		Physics::BoundingBox bounding;

		std::vector<BaseComponent*> collisionCall;

		virtual HitboxComponent* copy() const;
	
		template <class Archive>
		void serialize(Archive &ar)
		{
			ar(bounding.position.x);
			ar(bounding.position.y);
			ar(bounding.size.x);
			ar(bounding.size.y);
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
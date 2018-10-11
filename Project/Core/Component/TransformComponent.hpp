#ifndef TransformComponent_HPP
#define TransformComponent_HPP
#include "IBaseComponent.hpp"
#include "../Vector.h"
namespace Component
{
	class Transform : public IBaseComponent < Transform >
	{
	public:
		Transform();

		Transform(const Transform &tc);
		Core::Vector2 position;
		Core::Vector2 size;

		//Yet TBD
		Core::Vector2 rotation;

		double angle(Transform* target);

		double distance(Transform* target);

		Core::Vector2 DirectionTowards(Transform* target);

		//TODO move move() to protect or remove entirly
		//Move relative
		//void move(Vector2 dir,double s);
		virtual Transform* copy() const;
	
		template<class Archive>
		void serialize(Archive &ar)
		{
			//ar(tc.componentName);
			ar(position.x);
			ar(position.y);
			ar(rotation.x);
			ar(rotation.y);
			ar(size.x);
			ar(size.y);
		}
	protected:
		//Move towrads Absolute World coordinates with Pixel Per Seconds
		//void moveTo(Vector2 newPosition);

		void attachOn(GameObject* go);

	private:

		//template<class Archive>
		//friend void save(Archive &ar, const Transform &tc);
		//template<class Archive>
		//friend void load(Archive &ar, Transform &tc);
	};
}


#endif
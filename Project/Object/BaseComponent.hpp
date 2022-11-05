#ifndef BaseComponentTest_HPP
#define BaseComponentTest_HPP
#include <Helpers/Enum/ComponentType.hpp>
#include <Helpers\String.hpp>

class GameObject;
struct ComponentFactory;

namespace Component
{
	class Base
	{
	public:

		virtual void onCollision(GameObject* the_collidee) = 0;

		GameObject* attachedOn = nullptr;

		virtual Base* copy() const = 0;
		virtual std::unique_ptr<Base> ucopy() const = 0;

		virtual void detach() {};

		//Base(Base&&) = default;

	protected:

		friend class GameObject;
		friend struct ComponentFactory;

		virtual Enums::ComponentType getType() const = 0;

		virtual	Core::String getTypeName() const = 0;

		//HIGH: remove?
	public:
		virtual void Update() = 0;
		virtual void Simulate(const float& fElapsedTime) = 0;

		virtual void attachOn(GameObject* attachTo);

		virtual void onDeath() = 0;
		virtual void onDelete() {};

	public:
		virtual ~Base() = default;
	};
}


#endif
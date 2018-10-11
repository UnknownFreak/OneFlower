#ifndef BaseComponentTest_HPP
#define BaseComponentTest_HPP
#include <map>
#include "Message\BaseMessage.hpp"
#include <Core\String.hpp>
namespace Physics { class Collider; }

class GameObject;
struct ComponentFactory;
namespace Asset
{
	class Prefab;
}
namespace Component
{
	class Base
	{
	public:

		virtual void onCollision(Physics::Collider&);

		GameObject* attachedOn = NULL;

		virtual Base* copy() const = 0;

	protected:

		friend class GameObject;
		friend struct ComponentFactory;

		virtual const size_t getType() = 0;

		virtual	Core::String getTypeName() = 0;

		//HIGH: remove?
		virtual void update();

		virtual void attachOn(GameObject* attachTo);

		virtual void getMessage(const BaseMessage message);
#ifdef _DEBUG
		//friend class EngineWindow;
		friend class Asset::Prefab;

		//Copy of Registerd editor variables
		//virtual std::map<std::string,BaseField*> getFields() = 0;

		//update component whenever Editor change a variable value
		virtual bool updateFromEditor();
#endif

	public:
		virtual ~Base() = 0
		{
		};
		//template < class Archive>//, GameObject& go>
		//friend void save(Archive& archive, const Base& bc);
		//template < class Archive>//, GameObject& go>
		//friend void load(Archive& archive, Base& bc);
	};
}


#endif
#include "TransformComponent.hpp"
//#include <SFML\Graphics.hpp>
const unsigned int IBaseComponent<Component::TransformComponent>::typeID = 1001;
std::string IBaseComponent<Component::TransformComponent>::componentName = "TransformComponent";

namespace Component
{
	//a::Transform;
	TransformComponent::TransformComponent() :position(0, 0), rotation(0, 1), size(1, 1)
	{
	}
	TransformComponent::TransformComponent(const TransformComponent &tc) : position(tc.position.x, tc.position.y), rotation(tc.rotation.x, tc.rotation.y), size(tc.size.x, tc.size.y)
	{
	}
	void TransformComponent::attachOn(GameObject* go)
	{
		TransformComponent::BaseComponent::attachOn(go);
	}	
	TransformComponent * TransformComponent::copy()
	{
		return new TransformComponent(*this);
	}
}
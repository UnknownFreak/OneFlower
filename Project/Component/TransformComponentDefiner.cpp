#include "TransformComponent.hpp"
#include <SFML\Graphics.hpp>
const unsigned int IBaseComponent<TransformComponent>::typeID = 1001;
std::string IBaseComponent<TransformComponent>::componentName = "TransformComponent"; 

//std::string EditorField<std::string>::type = "test";
REGISTER_EDITOR_TYPE(int)
REGISTER_EDITOR_TYPE(float)
REGISTER_EDITOR_TYPE(double)
REGISTER_EDITOR_TYPE(bool)
REGISTER_EDITOR_TYPE(std::string)
REGISTER_EDITOR_TYPE(Vector2)
REGISTER_EDITOR_TYPE(std::vector<int>)
REGISTER_EDITOR_TYPE(std::vector<float>)
REGISTER_EDITOR_TYPE(std::vector<double>)
REGISTER_EDITOR_TYPE(std::vector<std::string>)
REGISTER_EDITOR_TYPE(sf::Uint8);

//a::Transform;
TransformComponent::TransformComponent():position(0,0),rotation(0,1),size(1,1)
{

}
TransformComponent::TransformComponent(const TransformComponent &tc):position(tc.position.x,tc.position.y),rotation(tc.rotation.x,tc.rotation.y),size(tc.size.x,tc.size.y)
{

}
void TransformComponent::attachOn(GameObject* go)
{
	TransformComponent::BaseComponent::attachOn(go);

	REGISTER_EDITOR_VARIABLE(Vector2,position,Position);
	REGISTER_EDITOR_VARIABLE(Vector2,rotation,Rotation);
	REGISTER_EDITOR_VARIABLE(Vector2,size,Size);

}

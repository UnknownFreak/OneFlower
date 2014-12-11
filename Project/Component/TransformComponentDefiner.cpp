#include "TransformComponent.hpp"
const unsigned int IBaseComponent<TransformComponent>::typeID = 1001;
std::string IBaseComponent<TransformComponent>::componentName = "TransformComponent"; 

//std::string EditorField<std::string>::type = "test";
REGISTER_EDITOR_TYPE(int)
REGISTER_EDITOR_TYPE(float)
REGISTER_EDITOR_TYPE(double)
REGISTER_EDITOR_TYPE(std::string)
REGISTER_EDITOR_TYPE(Vector2<int>)
REGISTER_EDITOR_TYPE(Vector2<float>)
REGISTER_EDITOR_TYPE(Vector2<double>)
REGISTER_EDITOR_TYPE(Vector2<std::string>)
REGISTER_EDITOR_TYPE(std::vector<int>)
REGISTER_EDITOR_TYPE(std::vector<float>)
REGISTER_EDITOR_TYPE(std::vector<double>)
REGISTER_EDITOR_TYPE(std::vector<std::string>)
//a::Transform;
TransformComponent::TransformComponent():position(0,0),rotation(1,1),size(1,1)
{
	REGISTER_EDITOR_VARIABLE(Vector2<int>,position,Position);
	REGISTER_EDITOR_VARIABLE(Vector2<int>,rotation,Rotation);
	REGISTER_EDITOR_VARIABLE(Vector2<int>,size,Size);

}
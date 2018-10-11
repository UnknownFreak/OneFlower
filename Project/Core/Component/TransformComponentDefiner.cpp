#include "TransformComponent.hpp"

namespace Component
{
	const size_t IBaseComponent<Component::Transform>::typeID = 1001;
	Core::String IBaseComponent<Component::Transform>::componentName = "Transform";
	//a::Transform;
	Transform::Transform() :position(0, 0), rotation(0, 1), size(1, 1)
	{
	}
	Transform::Transform(const Transform &tc) : position(tc.position.x, tc.position.y), rotation(tc.rotation.x, tc.rotation.y), size(tc.size.x, tc.size.y)
	{
	}
	void Transform::attachOn(GameObject* go)
	{
		Transform::Base::attachOn(go);
	}	
	Transform * Transform::copy() const
	{
		return new Transform(*this);
	}
}
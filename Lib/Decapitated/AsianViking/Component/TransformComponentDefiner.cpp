#include "TransformComponent.hpp"
unsigned int IBaseComponent<TransformComponent>::typeID = 1005;

TransformComponent::TransformComponent():position(0,0),rotation(1,1),size(1,1)
{
}
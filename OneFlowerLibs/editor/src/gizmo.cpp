#include <internal/gizmo.hpp>
//*
#pragma warning(push, 0)
#include <glm/gtc/quaternion.hpp>
#pragma warning(pop)

namespace of::editor
{

	void Gizmo::updateFrame(const float )
	{
	}

	void Gizmo::updateObjectTransform(std::shared_ptr<of::object::component::Transform> transform)
	{
		m_objects[0]->updateTransform(transform);
	}

	glm::vec3* Gizmo::getPos()
	{
		return &mTransform->pos;
	}

	glm::quat Gizmo::getRotation()
	{
		return glm::quat(mTransform->rot);
	}

	void Gizmo::setRotation(glm::quat& quat)
	{
		mTransform->rot = glm::eulerAngles(quat);
	}
}
//*/
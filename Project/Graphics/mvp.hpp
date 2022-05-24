#pragma once

#include <glm/glm.hpp>

namespace Graphics
{
	struct MVP
	{
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
		glm::vec4 eye;
	};

}
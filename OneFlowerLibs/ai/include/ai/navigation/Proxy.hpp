#pragma once

#include <file/FileId.hpp>
#include <utils/common/uuid.hpp>

#include <glm/vec3.hpp>

#include "../AIBehavior.hpp"

namespace of::ai
{
	class Proxy
	{
		of::file::FileId gameObjectProxyObjectClass;
		of::common::uuid onRecreateGameObjectInstanceId;

		glm::vec3 pos;

		std::shared_ptr<AIBehavior> behavior;

		inline void threadTick(const float& fElapsedTime) { behavior->onGameTick(fElapsedTime); };


	};
}
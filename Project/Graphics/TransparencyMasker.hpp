#pragma once

#include <Helpers/Rect.hpp>
#include <Module/Globals.hpp>
#include <Object/component/Transform.hpp>

struct TransparencyMasker
{
	Core::Rect<float> triggerTransparency{ glm::vec2{0.f, 0.f}, glm::vec2{128.f, 128.f } };
	Core::Rect<float> releaseTransparency{ glm::vec2{0.f, 0.f}, glm::vec2{256.f + 64.f, 256.f + 64.f } };
	std::shared_ptr<of::object::component::Transform> player = nullptr;

	//inline void setPos(Component::Transform* player)
	//{
	//	if (player == nullptr)
	//		return;
	//	auto pos = player->pos.toVector2();
	//	triggerTransparency.pos = pos - Core::Vector2f{ 64.f - 16.f, 64.f - 16.f };
	//	releaseTransparency.pos = pos - Core::Vector2f{ 128.f + 16.f, 128.f + 16.f };
	//	triggerTransparency.pos.y += player->buffered.z * Globals::Z_OFFSET;
	//	releaseTransparency.pos.y += player->buffered.z * Globals::Z_OFFSET;
	//}

	inline void update()
	{
		if (player == nullptr)
			return;
		auto pos = glm::vec2(player->pos);
		triggerTransparency.pos = pos - glm::vec2{ 64.f - 16.f, 64.f - 16.f };
		releaseTransparency.pos = pos - glm::vec2{ 128.f + 16.f, 128.f + 16.f };
		triggerTransparency.pos.y += player->buffered.z * Globals::Z_OFFSET;
		releaseTransparency.pos.y += player->buffered.z * Globals::Z_OFFSET;
	}

	//inline void triggersTransparency(Renderable* renderable, const int& currentZ)
	//{
	//	if (player == nullptr)
	//		return;
	//	if (triggerTransparency.intersects(renderable->drawBox) && float(currentZ) > player->buffered.z)
	//	{
	//		renderable->setTransparency(true);
	//		return;
	//	}
	//	//else if (releaseTransparency.contains(renderable->drawBox) && float(currentZ) > player->bufferedZ)
	//		renderable->setTransparency(false);
	//}
};
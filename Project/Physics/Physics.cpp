#include "Physics.hpp"
#include <Graphics/Window.hpp>
#include "Colliders/EntityCollider.hpp"
#include <Graphics/Window.hpp>
#include <ppl.h>

Enums::EngineResourceType Interfaces::IEngineResource<Physics::PhysicsEngine>::type = Enums::EngineResourceType::Physics;
namespace Physics
{

	void PhysicsEngine::runQuery(const Core::FloatRect& box)
	{
		auto visible_colliders = qt.query(box);
		auto& tree = qt;
		auto& eti = elapsedTimeInternal;
		Concurrency::parallel_for(size_t(0), visible_colliders.size(),
			[&visible_colliders, &tree, &eti](size_t idx)
		{
				auto it = visible_colliders[idx];
				auto ptr = it.ptr;
				if (ptr)
				{
					ptr->doParentSimulate(eti);
					if (ptr->colliderType == Enums::ColliderType::Entity)
					{
						auto possible_colliders = tree.query(it.rect);
						for (auto& collider : possible_colliders)
						{
							if (ptr != collider.ptr && collider.ptr != nullptr)
							{
								ptr->Collides(collider.ptr);
							}
						}
					}
					else if (ptr->colliderType == Enums::ColliderType::VisionHitbox)
					{
						auto possible_colliders = tree.query(it.rect);
						for (auto& collider : possible_colliders)
						{
							if (ptr != collider.ptr && collider.ptr != nullptr)
							{
								ptr->Collides(collider.ptr);
							}
						}
					}
					ptr->postUpdate();
				}
			}
		);
	}

	PhysicsEngine::PhysicsEngine() : qt({ -100000, -100000, 200000, 200000 }, getBox), renderBox(Engine::GetModule<Graphics::RenderWindow>().renderBox)
	{
	}

	PhysicsEngine::PhysicsEngine(const PhysicsEngine& copy) : qt(copy.qt), renderBox(copy.renderBox)
	{
	}
	void PhysicsEngine::update(const float& fElapsedTime)
	{
		elapsedTimeInternal = fElapsedTime;
		renderables.clear();
		runQuery({ -100000, -100000, 200000, 200000 });
		
		auto visible_colliders = qt.query(renderBox);
		for (auto& it : visible_colliders)
		{
			auto ptr = it.ptr;
			if (ptr)
			{
				//ptr->doParentSimulate(fElapsedTime);
				//ptr->doParentUpdate();
				if (ptr->colliderType == Enums::ColliderType::Entity)
				{
					renderables.push_back(((Collider*)ptr)->attachedOn);
					//auto possible_colliders = qt.query(it.rect);
					//std::sort(possible_colliders.begin(), possible_colliders.end(), [](BoxInfo a, BoxInfo b) {
					//	return (int)a.colliderType < (int)b.colliderType; });
					//for (auto& collider : possible_colliders)
					//{
					//	if (ptr != collider.ptr && collider.ptr != nullptr)
					//	{
					//		ptr->Collides(collider.ptr);
					//	}
					//}
					//ptr->postUpdate();
		
				}
				//else if (ptr->colliderType == Enums::ColliderType::VisionHitbox)
				//{
				//	auto possible_colliders = qt.query(it.rect);
				//	std::sort(possible_colliders.begin(), possible_colliders.end(), [](BoxInfo a, BoxInfo b) {
				//		return (int)a.colliderType < (int)b.colliderType; });
				//	for (auto& collider : possible_colliders)
				//	{
				//		if (ptr != collider.ptr && collider.ptr != nullptr)
				//		{
				//			ptr->Collides(collider.ptr);
				//		}
				//	}
				//	ptr->postUpdate();
				//
				//}
				else if (ptr->colliderType == Enums::ColliderType::StaticEntity)
				{
					renderables.push_back(((Collider*)ptr)->attachedOn);
					//ptr->postUpdate();
				}
			}
		}
//*/
		Engine::GetModule<Graphics::RenderWindow>().Cull(renderables);
	}
	void PhysicsEngine::addCollider(Interfaces::ICollider* collider)
	{
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Physics::PhysicsEngine").Debug("addCollider ", std::this_thread::get_id());
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Physics::PhysicsEngine").Debug(Core::toHex((size_t)collider));
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Physics::PhysicsEngine").Debug(
		collider->getBox().x, ", ", collider->getBox().y, ", ", collider->getBox().w, ", ", collider->getBox().h);
		qt.add(BoxInfo{size_t(collider), collider, collider->getBox(), collider->colliderType });
	}
	void PhysicsEngine::updateCollider(Interfaces::ICollider* collider, Interfaces::ICollider* newCollider, const Core::FloatRect& oldBox)
	{
		std::lock_guard lock(mtx);
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Physics::PhysicsEngine").Debug("updatingCollider", std::this_thread::get_id());
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Physics::PhysicsEngine").Debug("old ", Core::toHex((size_t)collider));
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Physics::PhysicsEngine").Debug("new ", Core::toHex((size_t)newCollider));
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Physics::PhysicsEngine").Debug(
			collider->getBox().x, ", ", collider->getBox().y, ", ", collider->getBox().w, ", ", collider->getBox().h);
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Physics::PhysicsEngine").Debug(
			newCollider->getBox().x, ", ", newCollider->getBox().y, ", ", newCollider->getBox().w, ", ", newCollider->getBox().h);
		qt.remove(BoxInfo{ size_t(collider), collider, oldBox, collider->colliderType });
		//auto visible_colliders = qt.query(renderBox);
		if (newCollider)
			qt.add(BoxInfo{ size_t(collider), newCollider, newCollider->getBox(), newCollider->colliderType });
		else
			qt.add(BoxInfo{ size_t(collider), nullptr, oldBox, Enums::ColliderType::Void });

	}
	void PhysicsEngine::removeCollider(Interfaces::ICollider* collider)
	{
		std::lock_guard lock(mtx);
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Physics::PhysicsEngine").Debug("removeCollider", std::this_thread::get_id());
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Physics::PhysicsEngine").Debug(Core::toHex((size_t)collider));
		Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("Physics::PhysicsEngine").Debug(
			collider->getBox().x, ", ", collider->getBox().y, ", ", collider->getBox().w, ", ", collider->getBox().h);
		qt.remove({size_t(collider), nullptr, collider->getBox(), Enums::ColliderType::Void });
	}
}
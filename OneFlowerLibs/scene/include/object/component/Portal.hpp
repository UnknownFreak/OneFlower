#pragma once

#include <object/component/BaseComponent.hpp>
#include <object/component/Transform.hpp>

#include <module/sceneManager.hpp>
#include <messaging/courier.hpp>

#include <glm/glm.hpp>

namespace of::object::component
{
	class Portal : public Base
	{
		
		virtual void onMessage(const of::object::messaging::Message& message) override
		{
			if (message.messageTopic == of::object::messaging::Topic::of(of::object::messaging::Topics::ON_COLLISION))
			{
				using namespace of::object::messaging;
				auto body = message.messageBody;
				std::shared_ptr<GameObjectPtr> go = std::dynamic_pointer_cast<GameObjectPtr>(body);
				if (go->go->tag == "player")
				{
					auto objectTrackingPos = go->go->getShared<of::object::component::Transform>();

					auto& courier = of::engine::GetModule<of::messaging::Courier>();
					courier.addSubscriber(of::messaging::Topic::Update,	of::messaging::Subscriber(instanceId, warrantyFromThis(),
						[this, objectTrackingPos](const of::messaging::Message& msg)
						{
							float distance = glm::abs(glm::distance(objectTrackingPos->pos,
							selfTrackingPos->pos));
					if (distance < teleportDistance)
					{
						teleport();
					}
					if (distance > guiHintDistance)
					{
						auto& courier = of::engine::GetModule<of::messaging::Courier>();
						courier.scheduleRemoval(of::messaging::Topic::Update, instanceId);
					}	
						}
					));
				}
			}
		};

		std::shared_ptr<of::object::component::Transform> selfTrackingPos;

		float teleportDistance;
		float guiHintDistance;

		virtual void initialize() override
		{
			selfTrackingPos = attachedOn->getShared<of::object::component::Transform>();
		}
		virtual void deconstruct() override
		{
			auto courier = of::engine::GetModule<of::messaging::Courier>();
			courier.removeSubscriber(of::messaging::Topic::Update, instanceId);
		}

		of::file::FileId world;
		of::file::FileId loadingScreen;
		// change pos coordinates to player pos marker object, that once the zone is loaded will teleport the player to the marker position.
		of::file::FileId positionMarker;
		glm::vec3 teleportPos;

		void teleport()
		{
			of::engine::GetModule<of::module::SceneManager>().loadWorldInstance(world, loadingScreen,
				teleportPos);
		}

	public:

		Portal() = default;
		~Portal() = default;

		virtual Portal* copy() const override
		{
			return new Portal(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override
		{
			return std::make_unique<Portal>(*this);
		}

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "Portal";
		};

		static constexpr of::common::uuid typeId = "4eb8d991-d06e-4231-b3bc-82e4b5d5199d";
	};
}
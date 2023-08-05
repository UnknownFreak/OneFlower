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
			using namespace of::object::messaging;
			if (message.messageTopic == Topic::of(Topics::ON_COLLISION))
			{
				std::shared_ptr<GameObjectPtr> messageBody = std::dynamic_pointer_cast<GameObjectPtr>(message.messageBody);
				// TODO: change tag to enum?
				if (messageBody->go->tag == "player")
				{
					auto objectTrackingPos = messageBody->go->getShared<of::object::component::Transform>();
					auto portalRef = attachedOn->getShared<Portal>();

					auto& courier = of::engine::GetModule<of::messaging::Courier>();

					// TODO: check if subscriber exists
					//if (courier.hasSubscriber(of::messaging::Topic::Update, instanceId))
					//	of::engine::GetModule<of::module::logger::OneLogger>().GetLogger("of::object::component::Portal").Info("Courier subscriber already exists, skipping!");
					//	return;

					courier.addSubscriber(
						of::messaging::Topic::Update,
						of::messaging::Subscriber(
							instanceId, warrantyFromThis(),
							[portalRef, objectTrackingPos] (const of::messaging::Message& msg)
							{
								float distance = glm::abs(glm::distance(objectTrackingPos->pos,
								portalRef->mSelfTrackingPos->pos));
								if (distance < portalRef->mTeleportDistance)
								{
									portalRef->teleport();
								}
								if (distance > portalRef->mGuiHintDistance)
								{
									auto& courier = of::engine::GetModule<of::messaging::Courier>();
									courier.scheduleRemoval(of::messaging::Topic::Update, portalRef->instanceId);
								}	
							}
						)
					);
				}
			}
		};

		std::shared_ptr<of::object::component::Transform> mSelfTrackingPos;

		float mTeleportDistance;
		float mGuiHintDistance;

		virtual void initialize() override
		{
			mSelfTrackingPos = attachedOn->getShared<of::object::component::Transform>();
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
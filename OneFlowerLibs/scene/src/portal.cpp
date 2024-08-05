#include <component/portal.hpp>

#include <module/sceneManager.hpp>
#include <courier/courier.hpp>

#include <input/inputHandler.hpp>

// TODO: move portal outside scene module?
namespace of::component
{
	void Portal::onMessage(const of::object::messaging::Message& message)
	{
		using namespace of::object::messaging;
		if (message.messageTopic == Topic::of(Topics::ON_COLLISION))
		{
			std::shared_ptr<GameObjectPtr> messageBody = std::dynamic_pointer_cast<GameObjectPtr>(message.messageBody);
			// TODO: change tag to enum?
			if (messageBody->go->tag == "player")
			{
				auto objectTrackingPos = messageBody->go->getShared<of::component::Transform>();
				auto portalRef = attachedOn->getShared<Portal>();

				auto& courier = of::courier::get();
				auto& inputHandler = of::engine::GetModule<of::input::InputHandler>();

				// TODO: check if subscriber exists
				//if (courier.hasSubscriber(of::messaging::Topic::Update, instanceId))
				//	of::engine::GetModule<of::logger::Logger>().GetLogger("of::object::component::Portal").Info("Courier subscriber already exists, skipping!");
				//	return;

				if (subscriberId == 0)
				{
					subscriberId = courier.addSubscriber(
						of::courier::Topic::Update,
						of::courier::Subscriber(
							isAlive(),
							[portalRef, objectTrackingPos, &inputHandler](const of::courier::Message&)
							{
								float distance = glm::abs(glm::distance(objectTrackingPos->pos,
									portalRef->mSelfTrackingPos->pos));
								if (distance < portalRef->mTeleportDistance)
								{
									if (portalRef->requireInteraction)
									{
										if (inputHandler.wasKeybindPressed("interact"))
										{
											portalRef->teleport();
											return;
										}
										// TODO: schedule a message later this frame to show the gui interaction prompt.
										//courier.schedulePost(of::messaging::Topic::GUI, );
									}
									else if (portalRef->requireInteraction == false)
									{
										portalRef->teleport();
									}
								}
								if (distance > portalRef->mGuiHintDistance)
								{
									of::courier::get().scheduleRemoval(of::courier::Topic::Update, portalRef->subscriberId);
									portalRef->subscriberId = 0;

								}
							}
						)
					);
				}
			}
		}
	}

	void Portal::attached()
	{
		mSelfTrackingPos = attachedOn->getShared<of::component::Transform>();
	}

	void Portal::initialize()
	{
	}

	void Portal::deconstruct()
	{
		if (subscriberId != 0)
		{
			of::courier::get().removeSubscriber(of::courier::Topic::Update, subscriberId);
			subscriberId = 0;
		}
	}

	void Portal::teleport()
	{
		of::engine::GetModule<of::module::SceneManager>().loadWorldInstance(world, loadingScreen, teleportPos);
	}
}

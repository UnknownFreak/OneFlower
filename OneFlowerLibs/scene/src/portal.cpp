#include <component/portal.hpp>

#include <scene/sceneManager.hpp>
#include <courier/courier.hpp>
#include <engine/courier/topic.hpp>

#include <input/inputHandler.hpp>

// TODO: move portal outside scene module?
namespace of::component
{
	void Portal::onMessage(const of::object::messaging::Message& message)
	{
		using Topic = of::object::messaging::Topic;
		using namespace of::object::messaging;
		if (message.messageTopic == Topic::of(Topics::ON_COLLISION))
		{
			std::shared_ptr<GameObjectPtr> messageBody = std::dynamic_pointer_cast<GameObjectPtr>(message.messageBody);
			// TODO: change tag to enum?
			if (messageBody->go->tag == "player")
			{
				auto objectTrackingPos = messageBody->go->getShared<of::component::Transform>();
				auto portalRef = attachedOn->getShared<Portal>();

				auto& courier = courier::get();
				auto inputHandler = of::input::InputHandler::GetInputSource();

				// TODO: check if subscriber exists
				//if (courier.hasSubscriber(of::messaging::Topic::Update, instanceId))
				//	of::logger::get().GetLogger("of::object::component::Portal").Info("Courier subscriber already exists, skipping!");
				//	return;

				if (subscriberId == courier::SubscriberId::NOT_SET)
				{
					using TTopic = of::engine::courier::Topic;
					constexpr auto to = of::Topic::convert;
					subscriberId = courier.addSubscriber(
						to(TTopic::Update),
						courier::Subscriber(
							isAlive(),
							[portalRef, objectTrackingPos, &inputHandler](const courier::Message&)
							{
								float distance = glm::abs(glm::distance(objectTrackingPos->pos,
									portalRef->mSelfTrackingPos->pos));
								if (distance < portalRef->mTeleportDistance)
								{
									if (portalRef->requireInteraction)
									{
										auto valid = inputHandler.lock();
										if (valid && valid->wasKeybindPressed("interact"))
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
									constexpr auto from = of::Topic::convert; 
									courier::get().scheduleRemoval(from(TTopic::Update), portalRef->subscriberId);
									portalRef->subscriberId = courier::SubscriberId::NOT_SET;

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
		if (subscriberId != courier::SubscriberId::NOT_SET)
		{
			using Topic = of::engine::courier::Topic;
			constexpr auto from = of::Topic::convert;

			courier::get().removeSubscriber(from(Topic::Update), subscriberId);
			subscriberId = courier::SubscriberId::NOT_SET;
		}
	}

	void Portal::teleport() const
	{
		if (auto valid = of::scene::SceneManager::GetSceneManager().lock())
		{
			valid->loadWorldInstance(world, loadingScreen, teleportPos);
		}
	}
}

#include <object/component/portal.hpp>

#include <module/sceneManager.hpp>
#include <messaging/courier.hpp>

#include <input/inputHandler.hpp>

// TODO: move portal outside scene module?
namespace of::object::component
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
						[portalRef, objectTrackingPos](const of::messaging::Message&)
						{
							float distance = glm::abs(glm::distance(objectTrackingPos->pos,
							portalRef->mSelfTrackingPos->pos));
							if (distance < portalRef->mTeleportDistance)
							{
								if (portalRef->requireInteraction)
								{
									// TODO: fix keybinds file
									if (true /* && of::engine::GetModule<of::input::InputHandler>().wasKeyPressed()*/ )
									{
										portalRef->teleport();
										return;
									}
									// TODO: schedule a message later this frame to show the gui interaction prompt.
									//courier.scheduledPost(of::messaging::Topic::GUI, );
								}
								else if (portalRef->requireInteraction == false)
								{
									portalRef->teleport();
								}
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
	}

	void Portal::initialize()
	{
		mSelfTrackingPos = attachedOn->getShared<of::object::component::Transform>();
	}

	void Portal::deconstruct()
	{
		auto courier = of::engine::GetModule<of::messaging::Courier>();
		courier.removeSubscriber(of::messaging::Topic::Update, instanceId);
	}

	void Portal::teleport()
	{
		of::engine::GetModule<of::module::SceneManager>().loadWorldInstance(world, loadingScreen, teleportPos);
	}
}
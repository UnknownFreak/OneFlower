#include "PlayerController.hpp"

#include <Object/GameObject.hpp>
#include <courier/courier.hpp>

namespace of::component
{
	void PlayerController::onMessage(const of::object::messaging::Message&)
	{
	}

	void PlayerController::attached()
	{
		mColliderType.hitType = of::physics::PxColliderType::Object;
		mColliderType.objectId = attachedOn->id;
		transform = attachedOn->get<Transform>();
		transform->speedModifier = 0.5f;
		combat = attachedOn->get<of::component::CombatComponent>();
		mActor = of::physics::get().createActorController(transform->pos);
		if (subscriberId == 0)
		{
			subscriberId = of::courier::get().addSubscriber(of::courier::Topic::PhysicsUpdate,
				of::courier::Subscriber(isAlive(), [this](const of::courier::Message& msg)
					{
						auto transform = attachedOn->get<Transform>();

						mActor->move({ 0, -9.81f, 0 }, 0.1f, msg.get<float>(), physx::PxControllerFilters());
						auto p = mActor->getFootPosition();
						transform->pos.x = (float)p.x;
						transform->pos.y = (float)p.y;
						transform->pos.z = (float)p.z;

					}));
		}
		mActor->getActor()->userData = &mColliderType;
		mActor->getActor()->setName("Player controller");

		enable();
	}

	void PlayerController::initialize() 
	{
	}

	void PlayerController::deconstruct()
	{
		if (subscriberId != 0)
		{
			of::courier::get().removeSubscriber(of::courier::Topic::PhysicsUpdate, subscriberId);
			subscriberId = 0;
		}
		if (of::physics::get().hasShutDown() == false && mActor != nullptr)
		{
			mActor->release();
			mActor = nullptr;
		}
		disable();
		clearBindings();
	}

	void PlayerController::clearBindings()
	{
		if (auto valid = handler.lock())
		{
			valid->playerKeyboard.removeCallback(swizzle::input::Keys::KeyE, "KbE<interact>", of::input::Action::Press);
			valid->playerKeyboard.removeCallback(swizzle::input::Keys::KeyW, "KbW<interact>", of::input::Action::Press);
			valid->playerKeyboard.removeCallback(swizzle::input::Keys::KeyS, "KbS<interact>", of::input::Action::Press);
			valid->playerKeyboard.removeCallback(swizzle::input::Keys::KeyA, "KbA<interact>", of::input::Action::Press);
			valid->playerKeyboard.removeCallback(swizzle::input::Keys::KeyD, "KbD<interact>", of::input::Action::Press);

			valid->playerKeyboard.removeCallback(swizzle::input::Keys::KeyW, "KbW", of::input::Action::Hold);
			valid->playerKeyboard.removeCallback(swizzle::input::Keys::KeyS, "KbS", of::input::Action::Hold);
			valid->playerKeyboard.removeCallback(swizzle::input::Keys::KeyA, "KbA", of::input::Action::Hold);
			valid->playerKeyboard.removeCallback(swizzle::input::Keys::KeyD, "KbD", of::input::Action::Hold);
			valid->playerKeyboard.removeCallback(swizzle::input::Keys::KeySpace, "Jmp", of::input::Action::Press);

			valid->mouse.removeCallback(swizzle::input::Mouse::LeftClick, "PAttack", of::input::Action::Press);

			//handler.controllerAxis.removeCallback(sf::Joystick::Y, "ControllerMoveY");
			//handler.controllerAxis.removeCallback(sf::Joystick::X, "ControllerMoveX");
			valid->controller.removeCallback(of::input::ControllerButtons::XB_A, "ControllerInteraction", of::input::Action::Press);
			valid->controller.removeCallback(of::input::ControllerButtons::XB_A, "ControllerJump", of::input::Action::Press);
		}
	}
	PlayerController::PlayerController() : handler(of::input::InputHandler::GetInputSource())
	{
		if (auto valid = handler.lock())
		{
			// TODO: change to gameobject->post(Topic::of(Topics::INTERACTION, std::make_shared<Interaction>(Things));
			valid->playerKeyboard.RegisterCallback(of::input::Callback::KeyboardCallbackTemp("KbE<interact>", [&](bool, swizzle::input::Keys, const float&) {
				if (!of::input::InputHandler::isMovementEnabled || !enabled) return;
				//attachedOn->interact(Enums::InteractionOption::Select);
				}, false), swizzle::input::Keys::KeyE, of::input::Action::Press);

			valid->playerKeyboard.RegisterCallback(of::input::Callback::KeyboardCallbackTemp("KbW<interact>", [&](bool, swizzle::input::Keys, const float&) {
				if (!of::input::InputHandler::isMovementEnabled || !enabled) return;
				//attachedOn->interact(Enums::InteractionOption::Up);
				}, false), swizzle::input::Keys::KeyW, of::input::Action::Press);
			valid->playerKeyboard.RegisterCallback(of::input::Callback::KeyboardCallbackTemp("KbS<interact>", [&](bool, swizzle::input::Keys, const float&) {
				if (!of::input::InputHandler::isMovementEnabled || !enabled) return;
				//attachedOn->interact(Enums::InteractionOption::Down);
				}, false), swizzle::input::Keys::KeyS, of::input::Action::Press);
			valid->playerKeyboard.RegisterCallback(of::input::Callback::KeyboardCallbackTemp("KbA<interact>", [&](bool, swizzle::input::Keys, const float&) {
				if (!of::input::InputHandler::isMovementEnabled || !enabled) return;
				//attachedOn->interact(Enums::InteractionOption::Left);
				}, false), swizzle::input::Keys::KeyA, of::input::Action::Press);
			valid->playerKeyboard.RegisterCallback(of::input::Callback::KeyboardCallbackTemp("KbD<interact>", [&](bool, swizzle::input::Keys, const float&) {
				if (!of::input::InputHandler::isMovementEnabled || !enabled) return;
				//attachedOn->interact(Enums::InteractionOption::Right);
				}, false), swizzle::input::Keys::KeyD, of::input::Action::Press);

			valid->playerKeyboard.RegisterCallback(of::input::Callback::KeyboardCallbackTemp("KbW", [&](bool, swizzle::input::Keys, const float& fElapsedTime) {
				if (!of::input::InputHandler::isMovementEnabled || !enabled) return;
				mActor->move({ 0, 0, -1.f * transform->speedModifier }, 0.1f, fElapsedTime, physx::PxControllerFilters());
				}, false), swizzle::input::Keys::KeyW, of::input::Action::Hold);
			valid->playerKeyboard.RegisterCallback(of::input::Callback::KeyboardCallbackTemp("KbS", [&](bool, swizzle::input::Keys, const float& fElapsedTime) {
				if (!of::input::InputHandler::isMovementEnabled || !enabled) return;
				mActor->move({ 0, 0, 1.f * transform->speedModifier }, 0.1f, fElapsedTime, physx::PxControllerFilters());
				}, false), swizzle::input::Keys::KeyS, of::input::Action::Hold);
			valid->playerKeyboard.RegisterCallback(of::input::Callback::KeyboardCallbackTemp("KbA", [&](bool, swizzle::input::Keys, const float& fElapsedTime) {
				if (!of::input::InputHandler::isMovementEnabled || !enabled) return;
				mActor->move({ -1.f * transform->speedModifier, 0, 0 }, 0.1f, fElapsedTime, physx::PxControllerFilters());
				}, false), swizzle::input::Keys::KeyA, of::input::Action::Hold);
			valid->playerKeyboard.RegisterCallback(of::input::Callback::KeyboardCallbackTemp("KbD", [&](bool, swizzle::input::Keys, const float& fElapsedTime) {
				if (!of::input::InputHandler::isMovementEnabled || !enabled) return;
				mActor->move({ 1.f * transform->speedModifier, 0, 0 }, 0.1f, fElapsedTime, physx::PxControllerFilters());
				}, false), swizzle::input::Keys::KeyD, of::input::Action::Hold);
			valid->playerKeyboard.RegisterCallback(of::input::Callback::KeyboardCallbackTemp("Jmp", [&](bool, swizzle::input::Keys, const float&) {
				if (!of::input::InputHandler::isMovementEnabled || !enabled) return;
				transform->jump();
				}, false), swizzle::input::Keys::KeySpace, of::input::Action::Press);

			//valid->mouse.RegisterCallback(of::input::Callback::MouseCallback("PAttack", [&](bool, sf::Mouse::Button, const float&) {
				//if (!of::input::InputHandler::isMovementEnabled || !enabled) return;
				//combat->execute(Enums::CombatSkill::Primary);
				//}), sf::Mouse::Button::Left, of::input::Action::Press);


			//valid->controllerAxis.RegisterCallback(of::input::Callback::AxisCallback("ControllerMoveY", [&](float dir, sf::Joystick::Axis, const float& fElapsedTime) {
			//	if (!of::input::InputHandler::isMovementEnabled) return;
			//	if (dir < 7.5 && dir > -7.5) return; transform->move({ 0, 2 * dir * fElapsedTime });
			//	}, false), sf::Joystick::Axis::Y);
			//valid->controllerAxis.RegisterCallback(of::input::Callback::AxisCallback("ControllerMoveX", [&](float dir, sf::Joystick::Axis, const float& fElapsedTime) {
			//	if (!of::input::InputHandler::isMovementEnabled) return;
			//	if (dir < 7.5 && dir > -7.5) return; transform->move({ 2 * dir * fElapsedTime, 0 });
			//	}, false), sf::Joystick::Axis::X);

			valid->controller.RegisterCallback(of::input::Callback::Callback<bool, of::input::ControllerButtons>("ControllerInteraction", [&](bool, of::input::ControllerButtons, const float&) {
				//of::input::InputHandler::skipCurrentFrame = attachedOn->interact(Enums::InteractionOption::Select);
				}, false), of::input::ControllerButtons::XB_A, of::input::Action::Press);
			valid->controller.RegisterCallback(of::input::Callback::Callback<bool, of::input::ControllerButtons>("ControllerJump", [&](bool, of::input::ControllerButtons, const float&) {
				if (!of::input::InputHandler::isMovementEnabled || of::input::InputHandler::skipCurrentFrame) return;
				transform->jump();
				}, false), of::input::ControllerButtons::XB_A, of::input::Action::Press);
		}
	}

	PlayerController::~PlayerController()
	{
		disable();
		clearBindings();
	}

	void PlayerController::disable()
	{
		enabled = false;
	}

	void PlayerController::enable()
	{
		enabled = true;
	}
}

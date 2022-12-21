#include "PlayerController.hpp"

#include <Object/GameObject.hpp>

of::common::uuid of::object::component::IBase<of::object::component::PlayerController>::typeID = of::common::uuid("4eb8d991-d06e-4231-b3bc-82e4b5d5199d");
of::common::String of::object::component::IBase<of::object::component::PlayerController>::componentName = "PlayerController";

namespace of::object::component
{
	void PlayerController::onMessage(const of::object::messaging::Message&)
	{
	}
	void PlayerController::clearBindings()
	{
		handler.playerKeyboard.removeCallback(swizzle::input::Keys::KeyE, "KbE<interact>", Enums::Input::Action::Press);
		handler.playerKeyboard.removeCallback(swizzle::input::Keys::KeyW, "KbW<interact>", Enums::Input::Action::Press);
		handler.playerKeyboard.removeCallback(swizzle::input::Keys::KeyS, "KbS<interact>", Enums::Input::Action::Press);
		handler.playerKeyboard.removeCallback(swizzle::input::Keys::KeyA, "KbA<interact>", Enums::Input::Action::Press);
		handler.playerKeyboard.removeCallback(swizzle::input::Keys::KeyD, "KbD<interact>", Enums::Input::Action::Press);

		handler.playerKeyboard.removeCallback(swizzle::input::Keys::KeyW, "KbW", Enums::Input::Action::Hold);
		handler.playerKeyboard.removeCallback(swizzle::input::Keys::KeyS, "KbS", Enums::Input::Action::Hold);
		handler.playerKeyboard.removeCallback(swizzle::input::Keys::KeyA, "KbA", Enums::Input::Action::Hold);
		handler.playerKeyboard.removeCallback(swizzle::input::Keys::KeyD, "KbD", Enums::Input::Action::Hold);
		handler.playerKeyboard.removeCallback(swizzle::input::Keys::KeySpace, "Jmp", Enums::Input::Action::Press);

		handler.mouse.removeCallback(swizzle::input::Mouse::LeftClick, "PAttack", Enums::Input::Action::Press);

		//handler.controllerAxis.removeCallback(sf::Joystick::Y, "ControllerMoveY");
		//handler.controllerAxis.removeCallback(sf::Joystick::X, "ControllerMoveX");
		handler.controller.removeCallback(Enums::Input::ControllerButtons::XB_A, "ControllerInteraction", Enums::Input::Action::Press);
		handler.controller.removeCallback(Enums::Input::ControllerButtons::XB_A, "ControllerJump", Enums::Input::Action::Press);
	}
	PlayerController::PlayerController() : handler(of::engine::GetModule<Input::InputHandler>()),
		window(of::engine::GetModule<Graphics::RenderWindow>())
	{
		// TODO: change to gameobject->post(Topic::of(Topics::INTERACTION, std::make_shared<Interaction>(Things));
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("KbE<interact>", [&](bool, swizzle::input::Keys, const float&) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			//attachedOn->interact(Enums::InteractionOption::Select);
			}, false), swizzle::input::Keys::KeyE, Enums::Input::Action::Press);

		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("KbW<interact>", [&](bool, swizzle::input::Keys, const float&) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			//attachedOn->interact(Enums::InteractionOption::Up);
			}, false), swizzle::input::Keys::KeyW, Enums::Input::Action::Press);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("KbS<interact>", [&](bool, swizzle::input::Keys, const float&) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			//attachedOn->interact(Enums::InteractionOption::Down);
			}, false), swizzle::input::Keys::KeyS, Enums::Input::Action::Press);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("KbA<interact>", [&](bool, swizzle::input::Keys, const float&) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			//attachedOn->interact(Enums::InteractionOption::Left);
			}, false), swizzle::input::Keys::KeyA, Enums::Input::Action::Press);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("KbD<interact>", [&](bool, swizzle::input::Keys, const float&) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			//attachedOn->interact(Enums::InteractionOption::Right);
			}, false), swizzle::input::Keys::KeyD, Enums::Input::Action::Press);

		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("KbW", [&](bool, swizzle::input::Keys, const float& fElapsedTime) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			transform->move({ 0, -200.f * fElapsedTime }); 
			}, false), swizzle::input::Keys::KeyW, Enums::Input::Action::Hold);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("KbS", [&](bool, swizzle::input::Keys, const float& fElapsedTime) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			transform->move({ 0, 200.f * fElapsedTime });
			}, false), swizzle::input::Keys::KeyS, Enums::Input::Action::Hold);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("KbA", [&](bool, swizzle::input::Keys, const float& fElapsedTime) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			transform->move({ -200.f * fElapsedTime, 0 });
			}, false), swizzle::input::Keys::KeyA, Enums::Input::Action::Hold);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("KbD", [&](bool, swizzle::input::Keys, const float& fElapsedTime) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			transform->move({ 200.f * fElapsedTime, 0 });
			}, false), swizzle::input::Keys::KeyD, Enums::Input::Action::Hold);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallbackTemp("Jmp", [&](bool, swizzle::input::Keys, const float&) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			transform->jump();
			}, false), swizzle::input::Keys::KeySpace, Enums::Input::Action::Press);

		//handler.mouse.RegisterCallback(Input::Callback::MouseCallback("PAttack", [&](bool, sf::Mouse::Button, const float&) {
			//if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			//combat->execute(Enums::CombatSkill::Primary);
			//}), sf::Mouse::Button::Left, Enums::Input::Action::Press);


		//handler.controllerAxis.RegisterCallback(Input::Callback::AxisCallback("ControllerMoveY", [&](float dir, sf::Joystick::Axis, const float& fElapsedTime) {
		//	if (!Input::InputHandler::isMovementEnabled) return;
		//	if (dir < 7.5 && dir > -7.5) return; transform->move({ 0, 2 * dir * fElapsedTime });
		//	}, false), sf::Joystick::Axis::Y);
		//handler.controllerAxis.RegisterCallback(Input::Callback::AxisCallback("ControllerMoveX", [&](float dir, sf::Joystick::Axis, const float& fElapsedTime) {
		//	if (!Input::InputHandler::isMovementEnabled) return;
		//	if (dir < 7.5 && dir > -7.5) return; transform->move({ 2 * dir * fElapsedTime, 0 });
		//	}, false), sf::Joystick::Axis::X);
		
		handler.controller.RegisterCallback(Input::Callback::Callback<bool, Enums::Input::ControllerButtons>("ControllerInteraction", [&](bool, Enums::Input::ControllerButtons, const float&) {
			//Input::InputHandler::skipCurrentFrame = attachedOn->interact(Enums::InteractionOption::Select);
			}, false), Enums::Input::ControllerButtons::XB_A, Enums::Input::Action::Press);
		handler.controller.RegisterCallback(Input::Callback::Callback<bool, Enums::Input::ControllerButtons>("ControllerJump", [&](bool, Enums::Input::ControllerButtons, const float&) {
			if (!Input::InputHandler::isMovementEnabled || Input::InputHandler::skipCurrentFrame) return;
			transform->jump();
			}, false), Enums::Input::ControllerButtons::XB_A, Enums::Input::Action::Press);
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

	void PlayerController::attachOn(GameObject* go)
	{
		Base::attachOn(go);
		window.getMasker().player = go->getSharedComponent<Transform>();
		transform = go->getComponent<Transform>();
		combat = go->getComponent<of::object::component::CombatComponent>();
		enable();
	}

	void PlayerController::onCollision(GameObject* )
	{
	}

	void PlayerController::Update()
	{
	}

	void PlayerController::Simulate(const float& )
	{
		//window.centerCameraOnObjectPos(transform->pos);
	}

	void PlayerController::onDeath()
	{
	}
}

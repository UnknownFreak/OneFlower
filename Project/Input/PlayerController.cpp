#include "PlayerController.hpp"

#include <Object/GameObject.hpp>

Enums::ComponentType Component::IBase<Component::PlayerController>::typeID = Enums::ComponentType::PlayerController;
Core::String Component::IBase<Component::PlayerController>::componentName = "PlayerController";

namespace Component
{
	void PlayerController::clearBindings()
	{
		handler.playerKeyboard.removeCallback(sf::Keyboard::Key::E, "KbE<interact>", Enums::Input::Action::Press);
		handler.playerKeyboard.removeCallback(sf::Keyboard::Key::W, "KbW<interact>", Enums::Input::Action::Press);
		handler.playerKeyboard.removeCallback(sf::Keyboard::Key::S, "KbS<interact>", Enums::Input::Action::Press);
		handler.playerKeyboard.removeCallback(sf::Keyboard::Key::A, "KbA<interact>", Enums::Input::Action::Press);
		handler.playerKeyboard.removeCallback(sf::Keyboard::Key::D, "KbD<interact>", Enums::Input::Action::Press);

		handler.playerKeyboard.removeCallback(sf::Keyboard::Key::W, "KbW", Enums::Input::Action::Hold);
		handler.playerKeyboard.removeCallback(sf::Keyboard::Key::S, "KbS", Enums::Input::Action::Hold);
		handler.playerKeyboard.removeCallback(sf::Keyboard::Key::A, "KbA", Enums::Input::Action::Hold);
		handler.playerKeyboard.removeCallback(sf::Keyboard::Key::D, "KbD", Enums::Input::Action::Hold);
		handler.playerKeyboard.removeCallback(sf::Keyboard::Key::Space, "Jmp", Enums::Input::Action::Press);

		handler.mouse.removeCallback(sf::Mouse::Button::Left, "PAttack", Enums::Input::Action::Press);

		handler.controllerAxis.removeCallback(sf::Joystick::Y, "ControllerMoveY");
		handler.controllerAxis.removeCallback(sf::Joystick::X, "ControllerMoveX");
		handler.controller.removeCallback(Enums::Input::ControllerButtons::XB_A, "ControllerInteraction", Enums::Input::Action::Press);
		handler.controller.removeCallback(Enums::Input::ControllerButtons::XB_A, "ControllerJump", Enums::Input::Action::Press);
	}
	PlayerController::PlayerController() : handler(Engine::GetModule<Input::InputHandler>()),
		window(Engine::GetModule<Graphics::RenderWindow>())
	{
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("KbE<interact>", [&](bool, sf::Keyboard::Key, const float&) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			attachedOn->interact(Enums::InteractionOption::Select);
			}, false), sf::Keyboard::Key::E, Enums::Input::Action::Press);

		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("KbW<interact>", [&](bool, sf::Keyboard::Key, const float&) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			attachedOn->interact(Enums::InteractionOption::Up);
			}, false), sf::Keyboard::Key::W, Enums::Input::Action::Press);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("KbS<interact>", [&](bool, sf::Keyboard::Key, const float&) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			attachedOn->interact(Enums::InteractionOption::Down);
			}, false), sf::Keyboard::Key::S, Enums::Input::Action::Press);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("KbA<interact>", [&](bool, sf::Keyboard::Key, const float&) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			attachedOn->interact(Enums::InteractionOption::Left);
			}, false), sf::Keyboard::Key::A, Enums::Input::Action::Press);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("KbD<interact>", [&](bool, sf::Keyboard::Key, const float&) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			attachedOn->interact(Enums::InteractionOption::Right);
			}, false), sf::Keyboard::Key::D, Enums::Input::Action::Press);

		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("KbW", [&](bool, sf::Keyboard::Key, const float& fElapsedTime) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			transform->move({ 0, -200.f * fElapsedTime }); 
			}, false), sf::Keyboard::Key::W, Enums::Input::Action::Hold);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("KbS", [&](bool, sf::Keyboard::Key, const float& fElapsedTime) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			transform->move({ 0, 200.f * fElapsedTime });
			}, false), sf::Keyboard::Key::S, Enums::Input::Action::Hold);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("KbA", [&](bool, sf::Keyboard::Key, const float& fElapsedTime) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			transform->move({ -200.f * fElapsedTime, 0 });
			}, false), sf::Keyboard::Key::A, Enums::Input::Action::Hold);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("KbD", [&](bool, sf::Keyboard::Key, const float& fElapsedTime) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			transform->move({ 200.f * fElapsedTime, 0 });
			}, false), sf::Keyboard::Key::D, Enums::Input::Action::Hold);
		handler.playerKeyboard.RegisterCallback(Input::Callback::KeyboardCallback("Jmp", [&](bool, sf::Keyboard::Key, const float&) {
			if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			transform->jump();
			}, false), sf::Keyboard::Key::Space, Enums::Input::Action::Press);

		//handler.mouse.RegisterCallback(Input::Callback::MouseCallback("PAttack", [&](bool, sf::Mouse::Button, const float&) {
			//if (!Input::InputHandler::isMovementEnabled || !enabled) return;
			//combat->execute(Enums::CombatSkill::Primary);
			//}), sf::Mouse::Button::Left, Enums::Input::Action::Press);


		handler.controllerAxis.RegisterCallback(Input::Callback::AxisCallback("ControllerMoveY", [&](float dir, sf::Joystick::Axis, const float& fElapsedTime) {
			if (!Input::InputHandler::isMovementEnabled) return;
			if (dir < 7.5 && dir > -7.5) return; transform->move({ 0, 2 * dir * fElapsedTime });
			}, false), sf::Joystick::Axis::Y);
		handler.controllerAxis.RegisterCallback(Input::Callback::AxisCallback("ControllerMoveX", [&](float dir, sf::Joystick::Axis, const float& fElapsedTime) {
			if (!Input::InputHandler::isMovementEnabled) return;
			if (dir < 7.5 && dir > -7.5) return; transform->move({ 2 * dir * fElapsedTime, 0 });
			}, false), sf::Joystick::Axis::X);
		
		handler.controller.RegisterCallback(Input::Callback::Callback<bool, Enums::Input::ControllerButtons>("ControllerInteraction", [&](bool, Enums::Input::ControllerButtons, const float&) {
			Input::InputHandler::skipCurrentFrame = attachedOn->interact(Enums::InteractionOption::Select);
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
		combat = go->getComponent<CombatComponent>();
		enable();
	}

	void PlayerController::onCollision(Interfaces::ICollider* )
	{
	}

	void PlayerController::Update()
	{
	}

	void PlayerController::Simulate(const float& )
	{
		window.centerCameraOnObjectPos(transform->pos);
	}

	void PlayerController::onDeath()
	{
	}
}

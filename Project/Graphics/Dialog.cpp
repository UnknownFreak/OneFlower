#include "Dialog.hpp"

#include <Module/Logger/OneLogger.hpp>
#include<Object/ObjectInstanceHandler.hpp>

Enums::ComponentType Component::IBase<Dialog>::typeID = Enums::ComponentType::Dialog;
of::common::String Component::IBase<Dialog>::componentName = "Dialog";

Enums::DialogStatus Dialog::navigate(const Enums::InteractionOption& navigation)
{
	return dialogTree.doSelection(navigation);
}

void Dialog::visualSelect(const glm::vec2& mousePosition)
{
	mousePosition;
}

of::common::String Dialog::getCurrentText()
{
	return dialogTree.getCurrentDialogString();
}

std::vector<of::common::String> Dialog::getDialogOptions()
{
	auto vec = dialogTree.getCurrentDialogOptions();
	if (dialogTree.hasDialogOptions())
	{
		vec[dialogTree.getPreviewSelection()] = "> " + vec[dialogTree.getPreviewSelection()];
	}
	return vec;
}

void Dialog::reset()
{
	dialogTree.reset();
}

void Dialog::attachOn(GameObject* go)
{
	Base::attachOn(go);
}

void Dialog::onCollision(GameObject*)
{
}

void Dialog::Update()
{
}

void Dialog::Simulate(const float& )
{
}

void Dialog::onDeath()
{
}

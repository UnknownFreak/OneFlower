#include "DialogTree.hpp"
#include <File/AssetManagerCore.hpp>
#include <Language/LanguageRequestor.hpp>

Core::uuid Interfaces::Trait<DialogTree>::typeId = Core::uuid("086e10f6-0ee5-4fd2-9091-e0af9bb1b2cd");

auto DialogTree::getString(const size_t& idx) const
{
	if (idx == size_t(-1))
		return Core::String("");
	auto& x = Engine::GetModule<Asset::AssetManager>().getLanguage();
	auto uid = dialogStrings.at(idx).dialogString;
	return dialogStrings.at(idx).tempText + x.getString(uid);
}

bool DialogTree::canPlayerAccessDialogOption(const DialogOptionId& optionId) const
{
	if (optionId == DialogOptionId(-1))
		return true;
	if (dialogStrings.at(optionId).optionRequirement)
		return dialogStrings.at(optionId).optionRequirement->fullfilled();
	return true;
}

bool DialogTree::incrementSelection()
{
	size_t limit = 0;
	do
	{
		limit++;
		previewSelection++;
		if (previewSelection >= dialogStrings[currentSelection].dialogOptions.size())
			previewSelection = 0;
	} while (!canPlayerAccessDialogOption(dialogStrings[currentSelection].dialogOptions[previewSelection].first) && limit < 50);
	return limit < 50;
}

bool DialogTree::decrementSelection()
{
	size_t limit = 0;
	do
	{
		limit++;
		previewSelection--;
		if (previewSelection == 0xffffffffffffffff)
			previewSelection = dialogStrings[currentSelection].dialogOptions.size() - 1;
	} while (!canPlayerAccessDialogOption(dialogStrings[currentSelection].dialogOptions[previewSelection].first) && limit < 50);
	return limit < 50;
}

DialogTree::DialogTree(std::unordered_map<size_t, DialogOption>& um) : dialogStrings(um)
{
	reset();
}

size_t DialogTree::getPreviewSelection() const
{
	return previewSelection;
}

std::vector<Core::String> DialogTree::getCurrentDialogOptions()
{
	auto vec = std::vector<Core::String>();
	for (std::pair<DialogOptionId, ResponseValueId> u : dialogStrings[currentSelection].dialogOptions)
	{
		if (canPlayerAccessDialogOption(u.first))
			vec.push_back(getString(u.first));
	}
	max_index = vec.size();
	return vec;
}

Core::String DialogTree::getCurrentDialogString()
{
	return getString(currentSelection);
}

Enums::DialogStatus DialogTree::doSelection(const Enums::InteractionOption& option)
{
	if (option == Enums::InteractionOption::Select)
	{
		auto selection = currentSelection;
		if(hasDialogOptions())
			currentSelection = dialogStrings[selection].dialogOptions[previewSelection].second;
		previewSelection = 0;

		if (dialogStrings[selection].onDialogActivatedTrigger)
			dialogStrings[selection].onDialogActivatedTrigger->execute();
		return dialogStrings[selection].selectionStatus;
	}
	else if (option == Enums::InteractionOption::Close)
		return Enums::DialogStatus::Close;

	else if (hasDialogOptions() && option == Enums::InteractionOption::Down)
	{
		if (!incrementSelection())
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("DialogTree").Error(this->getModfile().operator()() + " DialogOptionId [" + std::to_string(currentSelection) + "] got stuck in a loop while going to next option");
			return Enums::DialogStatus::Close;
		}
	}
	else if (hasDialogOptions() && option == Enums::InteractionOption::Up)
	{
		if (!decrementSelection())
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("DialogTree").Error(this->getModfile().operator()() + " DialogOptionId [" + std::to_string(currentSelection) + "] got stuck in a loop while going to next option");
			return Enums::DialogStatus::Close;
		}
	}

	return Enums::DialogStatus::Open;
}

bool DialogTree::hasDialogOptions()
{
	return max_index > 0;
}

void DialogTree::reset()
{
	currentSelection = 0;
	previewSelection = 0;
}

Interfaces::TypeInfo DialogTree::getTrait() const
{
	return { Interfaces::Trait<DialogTree>::typeId };
}

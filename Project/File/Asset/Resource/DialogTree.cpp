#include "DialogTree.hpp"
#include <file/Handler.hpp>
#include <locale/Translatable.hpp>

of::common::uuid of::file::archive::Trait<Asset::Resource::DialogTree>::typeId = of::common::uuid("086e10f6-0ee5-4fd2-9091-e0af9bb1b2cd");

namespace Asset::Resource
{

	auto DialogTree::getString(const size_t& idx) const
	{
		if (idx == size_t(-1))
			return of::common::String("");
		//auto& x = of::engine::GetModule<of::file::Handler>().getLanguage();
		auto uid = dialogStrings.at(idx).dialogString;
		return dialogStrings.at(idx).tempText + of::locale::Translatable(uid).value;
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

	std::vector<of::common::String> DialogTree::getCurrentDialogOptions()
	{
		auto vec = std::vector<of::common::String>();
		for (std::pair<DialogOptionId, ResponseValueId> u : dialogStrings[currentSelection].dialogOptions)
		{
			if (canPlayerAccessDialogOption(u.first))
				vec.push_back(getString(u.first));
		}
		max_index = vec.size();
		return vec;
	}

	of::common::String DialogTree::getCurrentDialogString()
	{
		return getString(currentSelection);
	}

	Enums::DialogStatus DialogTree::doSelection(const Enums::InteractionOption& option)
	{
		if (option == Enums::InteractionOption::Select)
		{
			auto selection = currentSelection;
			if (hasDialogOptions())
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
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("DialogTree").Error(this->getModfile().operator()() + " DialogOptionId [" + std::to_string(currentSelection) + "] got stuck in a loop while going to next option");
				return Enums::DialogStatus::Close;
			}
		}
		else if (hasDialogOptions() && option == Enums::InteractionOption::Up)
		{
			if (!decrementSelection())
			{
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("DialogTree").Error(this->getModfile().operator()() + " DialogOptionId [" + std::to_string(currentSelection) + "] got stuck in a loop while going to next option");
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

	of::file::archive::TypeInfo DialogTree::getTrait() const
	{
		return { of::file::archive::Trait<DialogTree>::typeId };
	}
}
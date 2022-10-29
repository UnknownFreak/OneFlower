#ifndef DialogTree_HPP
#define DialogTree_HPP

#include <Interfaces/IRequestable.hpp>
#include <Helpers/Enum/InteractionOption.hpp>
#include <Helpers/Enum/DialogStatus.hpp>
#include <unordered_map>
#include <vector>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>

#include <Requirement/Requirement.hpp>
#include <Trigger/Trigger.hpp>

namespace Asset::Resource
{
	struct DialogOption
	{
		typedef size_t DialogOptionId;
		typedef size_t ResponseValueId;
		Core::uuid dialogString;
		std::vector<std::pair<DialogOptionId, ResponseValueId>> dialogOptions;
		Requirement::Requirement* optionRequirement;
		Trigger::Trigger* onDialogActivatedTrigger;
		Enums::DialogStatus selectionStatus;
		Core::String tempText;

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(dialogString);
			ar(dialogOptions);
			ar(selectionStatus);
			{
				// TODO: fixme! change member variable to not use raw pointer...
				auto tmp = std::unique_ptr<Requirement::Requirement>((Requirement::Requirement*)optionRequirement);
				ar(tmp);
				tmp.release();
			}
			{
				// TODO: fixme! change member variable to not use raw pointer...
				auto tmp = std::unique_ptr<Trigger::Trigger>((Trigger::Trigger*)onDialogActivatedTrigger);
				ar(tmp);
				tmp.release();
			}
		}
		template<class Archive>
		void load(Archive& ar)
		{
			ar(dialogString);
			ar(dialogOptions);
			ar(selectionStatus);
			{
				std::unique_ptr<Requirement::Requirement> tmp;
				ar(tmp);
				optionRequirement = tmp.release();
			}
			{
				std::unique_ptr<Trigger::Trigger> tmp;
				ar(tmp);
				onDialogActivatedTrigger = tmp.release();
			}
		}
	};

	class DialogTree : public Interfaces::IRequestable
	{
		typedef size_t DialogOptionId;
		typedef size_t ResponseValueId;
		size_t currentSelection;
		size_t previewSelection;
		size_t max_index = 0;

		std::unordered_map<size_t, DialogOption> dialogStrings;

		auto getString(const size_t& stringindex) const;
		bool canPlayerAccessDialogOption(const DialogOptionId& optionId) const;
		//void doTriggerIfExists(const unsigned& idx);

		bool incrementSelection();
		bool decrementSelection();
	public:

		DialogTree() = default;
		DialogTree(std::unordered_map<size_t, DialogOption>& um);

		size_t getPreviewSelection() const;
		std::vector<Core::String> getCurrentDialogOptions();
		Core::String getCurrentDialogString();
		Enums::DialogStatus doSelection(const Enums::InteractionOption& option);
		bool hasDialogOptions();

		void reset();

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(fromMod);
			ar(ID);
			ar(mode);
			ar(objectType);
			ar(objectVersion);
			ar(dialogStrings);
		}
		template<class Archive>
		void load(Archive& ar)
		{
			ar(fromMod);
			ar(ID);
			ar(mode);
			ar(objectType);
			ar(objectVersion);
			ar(dialogStrings);
		}

		// Inherited via IRequestable
		virtual Interfaces::TypeInfo getTrait() const override;
	};

}

#endif // !DialogTree_HPP

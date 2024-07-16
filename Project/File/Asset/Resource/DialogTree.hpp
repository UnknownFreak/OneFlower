#ifndef DialogTree_HPP
#define DialogTree_HPP

#include <file/archive/Requestable.hpp>
#include <Helpers/Enum/InteractionOption.hpp>
#include <Helpers/Enum/DialogStatus.hpp>
#include <unordered_map>
#include <vector>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>

#include <Requirement/Requirement.hpp>
#include <trigger/Trigger.hpp>

namespace Asset::Resource
{
	struct DialogOption
	{
		typedef size_t DialogOptionId;
		typedef size_t ResponseValueId;
		of::common::uuid dialogString;
		std::vector<std::pair<DialogOptionId, ResponseValueId>> dialogOptions;
		Requirement::Requirement* optionRequirement;
		of::trigger::Trigger* onDialogActivatedTrigger;
		Enums::DialogStatus selectionStatus;
		of::common::String tempText;

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
				auto tmp = std::unique_ptr<of::trigger::Trigger>((of::trigger::Trigger*)onDialogActivatedTrigger);
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
				std::unique_ptr<of::trigger::Trigger> tmp;
				ar(tmp);
				onDialogActivatedTrigger = tmp.release();
			}
		}
	};

	class DialogTree : public of::file::archive::Requestable
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
		std::vector<of::common::String> getCurrentDialogOptions();
		of::common::String getCurrentDialogString();
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
		virtual of::file::archive::TypeInfo getTrait() const override;
	};

}
CEREAL_REGISTER_TYPE(Asset::Resource::DialogTree);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, Asset::Resource::DialogTree);

#endif // !DialogTree_HPP

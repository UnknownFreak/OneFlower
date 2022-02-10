#ifdef _UNITTESTS_
#include "CppUnitTest.h"

#include <Items/Item.hpp>

#include <Quest/QuestObjective.hpp>
#include <Quest/CollectItemObjective.hpp>

#include <File/SaveFile.hpp>
#include <Items/Inventory.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace TQuesting
	{

	TEST_CLASS(CollectItemQuestObjectiveTest)
	{
	public:

		static Items::Base b;
		static Items::Base b2;
		static Questing::CollectItemObjective q;
		static size_t objectiveId;
		static size_t completed_state;
		static size_t failed_state;

		TEST_CLASS_INITIALIZE(Initialize)
		{
			auto& saveFile = Engine::GetModule<File::SaveFile>();
			saveFile.player.addComponent<Component::Inventory>();
			auto inventory = saveFile.player.getComponent<Component::Inventory>();

			b.ID = Core::uuid();
			b2.ID = Core::uuid();

			q.objectiveId = objectiveId;
			q.nextQuestObjectiveStateId = completed_state;
			q.failedObjectiveStateId = failed_state;
			q.itemCount = 10;
			q.itemId = b.getModfile();
			b.stackSize = 10;
			inventory->itemList.push_back(std::make_shared<Items::Base>(b));
			b.stackSize = 0;
		}

		TEST_METHOD_INITIALIZE(MethodInit)
		{
			q.objectiveState = Enums::QuestState::NOT_ACTIVE;
			q.completeOnPendingComplete = false;
		}

		TEST_METHOD(addItem_CollectItemObjective)
		{
			b.stackSize = 10;
			q.objectiveState = Enums::QuestState::ACTIVE;
			Assert::AreEqual<size_t>(q.onItemPickUp(&b), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
		}
		TEST_METHOD(addItem_Partial_CollectItemObjective)
		{
			b.stackSize = 2;
			q.objectiveState = Enums::QuestState::ACTIVE;
			Assert::AreEqual<size_t>(q.onItemPickUp(&b), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
		}
		TEST_METHOD(addItem_NotActive_CollectItemObjective)
		{
			b.stackSize = 10;
			q.objectiveState = Enums::QuestState::NOT_ACTIVE;
			Assert::AreEqual<size_t>(q.onItemPickUp(&b), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
		}
		TEST_METHOD(addItem_CompleteOnPendingComplete_CollectItemObjective)
		{
			b.stackSize = 10;
			q.objectiveState = Enums::QuestState::ACTIVE;
			q.completeOnPendingComplete = true;
			Assert::AreEqual<size_t>(q.onItemPickUp(&b), completed_state);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
		}
		TEST_METHOD(removeItem_CollectItemObjective)
		{
			b.stackSize = 4;
			q.objectiveState = Enums::QuestState::PENDING_COMPLETE;
			Assert::AreEqual<size_t>(q.onItemDropped(&b), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
		}
		TEST_METHOD(removeItem_ObjectiveComplete_CollectItemObjective)
		{
			b.stackSize = 4;
			q.objectiveState = Enums::QuestState::COMPLETE;
			Assert::AreEqual<size_t>(q.onItemDropped(&b), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
		}
		TEST_METHOD(removeItem_PendingComplete_AboveStackCount_CollectItemObjective)
		{
			b.stackSize = 10;
			q.objectiveState = Enums::QuestState::PENDING_COMPLETE;
			Assert::AreEqual<size_t>(q.onItemDropped(&b), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
		}

		TEST_METHOD(activateObjectiveWhenAllItemsCollected_ShouldSetPendingComplete)
		{
			q.activateObjective();
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
		}

		TEST_METHOD(addItem_WrongItem_CollectItemObjective)
		{
			b2.stackSize = 10;
			q.objectiveState = Enums::QuestState::ACTIVE;
			Assert::AreEqual<size_t>(q.onItemPickUp(&b2), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
		}
		TEST_METHOD(addItem_WrongItem_Partial_CollectItemObjective)
		{
			b2.stackSize = 2;
			q.objectiveState = Enums::QuestState::ACTIVE;
			Assert::AreEqual<size_t>(q.onItemPickUp(&b2), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
		}
		TEST_METHOD(addItem_WrongItem_NotActive_CollectItemObjective)
		{
			b2.stackSize = 10;
			q.objectiveState = Enums::QuestState::NOT_ACTIVE;
			Assert::AreEqual<size_t>(q.onItemPickUp(&b2), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
		}
		TEST_METHOD(addItem_WrongItem_CompleteOnPendingComplete_CollectItemObjective)
		{
			b2.stackSize = 10;
			q.objectiveState = Enums::QuestState::ACTIVE;
			q.completeOnPendingComplete = true;
			Assert::AreEqual<size_t>(q.onItemPickUp(&b2), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
		}
		TEST_METHOD(removeItem_WrongItem_CollectItemObjective)
		{
			b2.stackSize = 4;
			q.objectiveState = Enums::QuestState::PENDING_COMPLETE;
			Assert::AreEqual<size_t>(q.onItemDropped(&b2), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
		}
		TEST_METHOD(removeItem_WrongItem_ObjectiveComplete_CollectItemObjective)
		{
			b2.stackSize = 4;
			q.objectiveState = Enums::QuestState::COMPLETE;
			Assert::AreEqual<size_t>(q.onItemDropped(&b2), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
		}
		TEST_METHOD(removeItem_WrongItem_PendingComplete_AboveStackCount_CollectItemObjective)
		{
			b2.stackSize = 10;
			q.objectiveState = Enums::QuestState::PENDING_COMPLETE;
			Assert::AreEqual<size_t>(q.onItemDropped(&b2), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
		}
	};
	Questing::CollectItemObjective CollectItemQuestObjectiveTest::q;
	Items::Base CollectItemQuestObjectiveTest::b;
	Items::Base CollectItemQuestObjectiveTest::b2;
	size_t CollectItemQuestObjectiveTest::objectiveId = 1;
	size_t CollectItemQuestObjectiveTest::completed_state = 2;
	size_t CollectItemQuestObjectiveTest::failed_state = 3;
	}
}

#endif
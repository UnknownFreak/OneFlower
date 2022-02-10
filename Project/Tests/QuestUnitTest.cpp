#ifdef _UNITTESTS_
#include "CppUnitTest.h"
#include <Tests/TestObjects.hpp>

#include <Quest/Quest.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace TQuesting
	{

		TEST_CLASS(QuestTest)
		{
		public:

			static Questing::Quest q;

			DummyObjective* as(std::unique_ptr<Questing::QuestObjective>& ptr)
			{
				return (DummyObjective*)ptr.get();
			}

			TEST_CLASS_INITIALIZE(Initialize)
			{
				q.objectiveMap[size_t(0)] = std::make_unique<DummyObjective>();
				q.objectiveMap[size_t(0)]->objectiveId = 0;
				q.objectiveMap[size_t(0)]->nextQuestObjectiveStateId = 1;
				q.objectiveMap[size_t(0)]->failedObjectiveStateId = 1;
				q.objectiveMap[size_t(1)] = std::make_unique<DummyObjective>();
				q.objectiveMap[size_t(1)]->objectiveId = 1;
				q.objectiveMap[size_t(1)]->nextQuestObjectiveStateId = 2222;
				q.objectiveMap[size_t(1)]->failedObjectiveStateId = 9999;

				q.failedStateId = 9999;
				q.completedStateId = 2222;

			}

			TEST_METHOD_INITIALIZE(MethodInit)
			{
				q.questState = Enums::QuestState::NOT_ACTIVE;
				q.requireInteractionOnPendingObjectives = true;
				q.currentObjectiveId = 0;
				q.objectiveMap[size_t(0)]->objectiveState = Enums::QuestState::NOT_ACTIVE;
				as(q.objectiveMap[size_t(0)])->completeOnCall = false;
				as(q.objectiveMap[size_t(0)])->failOnCall = false;
				as(q.objectiveMap[size_t(0)])->completeOrFailOnCall = false;
				q.objectiveMap[size_t(1)]->objectiveState = Enums::QuestState::NOT_ACTIVE;
				as(q.objectiveMap[size_t(1)])->completeOnCall = false;
				as(q.objectiveMap[size_t(1)])->failOnCall = false;
				as(q.objectiveMap[size_t(1)])->completeOrFailOnCall = false;
				q.startQuest();

			}

			TEST_METHOD(startedQuest)
			{
				Assert::AreEqual<int>((int)q.questState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(0)]->objectiveState, (int)Enums::QuestState::ACTIVE);
			}
			TEST_METHOD(completeQuest)
			{
				q.completeQuest();
				Assert::AreEqual<int>((int)q.questState, (int)Enums::QuestState::COMPLETE);
			}
			TEST_METHOD(failQuest)
			{
				q.failQuest();
				Assert::AreEqual<int>((int)q.questState, (int)Enums::QuestState::FAILED);
			}

			TEST_METHOD(resetCurrentObjective)
			{
				q.objectiveMap[size_t(0)]->objectiveState = Enums::QuestState::PENDING_FAILURE;
				q.resetCurrentObjective();
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(0)]->objectiveState, (int)Enums::QuestState::ACTIVE);
			}

			TEST_METHOD(completeObjectiveNextStarts)
			{
				as(q.objectiveMap[size_t(0)])->completeOnCall = true;
				q.onEnemyDefeated(nullptr);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(0)]->objectiveState, (int)Enums::QuestState::COMPLETE);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(1)]->objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<size_t>(q.currentObjectiveId, q.objectiveMap[1]->objectiveId);
			}
			TEST_METHOD(failObjectiveNextStarts)
			{
				as(q.objectiveMap[size_t(0)])->failOnCall = true;
				q.onEnemyDefeated(nullptr);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(0)]->objectiveState, (int)Enums::QuestState::FAILED);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(1)]->objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<size_t>(q.currentObjectiveId, q.objectiveMap[1]->objectiveId);
			}

			TEST_METHOD(completeObjectiveQuestCompletes)
			{
				as(q.objectiveMap[size_t(1)])->completeOnCall = true;
				q.currentObjectiveId = 1;
				q.onEnemyDefeated(nullptr);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(1)]->objectiveState, (int)Enums::QuestState::COMPLETE);
				Assert::AreEqual<int>((int)q.questState, (int)Enums::QuestState::COMPLETE);
				Assert::AreEqual<size_t>(q.currentObjectiveId, q.completedStateId);
			}
			TEST_METHOD(failObjectiveQuestFails)
			{
				as(q.objectiveMap[size_t(1)])->failOnCall = true;
				q.currentObjectiveId = 1;

				q.onEnemyDefeated(nullptr);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(1)]->objectiveState, (int)Enums::QuestState::FAILED);
				Assert::AreEqual<int>((int)q.questState, (int)Enums::QuestState::FAILED);
				Assert::AreEqual<size_t>(q.currentObjectiveId, q.failedStateId);
			}

			TEST_METHOD(npcInteractCompletesObjectiveIfPendingComplete)
			{
				q.objectiveMap[size_t(0)]->objectiveState = Enums::QuestState::PENDING_COMPLETE;
				q.interactWithNpc();
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(0)]->objectiveState, (int)Enums::QuestState::COMPLETE);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(1)]->objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<size_t>(q.currentObjectiveId, q.objectiveMap[1]->objectiveId);
			}
			TEST_METHOD(npcInteractFailsObjectiveIfPendingFailure)
			{
				q.objectiveMap[size_t(0)]->objectiveState = Enums::QuestState::PENDING_FAILURE;
				q.interactWithNpc();
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(0)]->objectiveState, (int)Enums::QuestState::FAILED);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(1)]->objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<size_t>(q.currentObjectiveId, q.objectiveMap[1]->objectiveId);
			}
			TEST_METHOD(npcInteractNothingHappensIfActive)
			{
				q.interactWithNpc();
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(0)]->objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(1)]->objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
				Assert::AreEqual<size_t>(q.currentObjectiveId, q.objectiveMap[0]->objectiveId);
			}


			TEST_METHOD(onXObjectiveIfPendingCompleteNoProgress)
			{
				q.objectiveMap[size_t(0)]->objectiveState = Enums::QuestState::PENDING_COMPLETE;

				q.onEnemyDefeated(nullptr);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(0)]->objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(1)]->objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
				Assert::AreEqual<size_t>(q.currentObjectiveId, q.objectiveMap[0]->objectiveId);
			}
			TEST_METHOD(onXObjectiveIfPendingFailureNoProgress)
			{
				q.objectiveMap[size_t(0)]->objectiveState = Enums::QuestState::PENDING_FAILURE;
				q.onEnemyDefeated(nullptr);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(0)]->objectiveState, (int)Enums::QuestState::PENDING_FAILURE);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(1)]->objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
				Assert::AreEqual<size_t>(q.currentObjectiveId, q.objectiveMap[0]->objectiveId);
			}

			TEST_METHOD(onXObjectiveIfPendingCompleteNoProgressNotRequireNpcInteraction)
			{
				q.objectiveMap[size_t(0)]->objectiveState = Enums::QuestState::PENDING_COMPLETE;
				as(q.objectiveMap[size_t(0)])->completeOrFailOnCall = true;
				q.requireInteractionOnPendingObjectives = false;

				q.onEnemyDefeated(nullptr);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(0)]->objectiveState, (int)Enums::QuestState::COMPLETE);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(1)]->objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<size_t>(q.currentObjectiveId, q.objectiveMap[1]->objectiveId);
			}
			TEST_METHOD(onXObjectiveIfPendingFailureNoProgressNotRequireNpcInteraction)
			{
				q.objectiveMap[size_t(0)]->objectiveState = Enums::QuestState::PENDING_FAILURE;
				as(q.objectiveMap[size_t(0)])->completeOrFailOnCall = true;
				q.requireInteractionOnPendingObjectives = false;

				q.onEnemyDefeated(nullptr);
				Assert::AreEqual<int>((int)q.objectiveMap[size_t(0)]->objectiveState, (int)Enums::QuestState::FAILED);
				Assert::AreEqual<size_t>(q.currentObjectiveId, q.objectiveMap[1]->objectiveId);
			}
		};

		Questing::Quest QuestTest::q;

	}
}

#endif
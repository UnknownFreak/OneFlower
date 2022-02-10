#ifdef _UNITTESTS_
#include "CppUnitTest.h"
#include <Tests/TestObjects.hpp>

#include <Object/GameObject.hpp>
#include <Quest/ListObjective.hpp>
#include <Tests/TestObjects.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{

	namespace TQuesting
	{

		TEST_CLASS(ListQuestObjectiveTest)
		{

		public:

			static Questing::ListObjective q;
			static size_t objectiveId;
			static size_t completed_state;
			static size_t failed_state;

			TEST_CLASS_INITIALIZE(Initialize)
			{

				q.objectiveId = objectiveId;
				q.nextQuestObjectiveStateId = completed_state;
				q.failedObjectiveStateId = failed_state;
				q.list.push_back(std::move(std::make_unique<DummyObjective>()));
				q.list.push_back(std::move(std::make_unique<DummyObjective>()));
			}

			TEST_METHOD_INITIALIZE(MethodInit)
			{
				q.objectiveState = Enums::QuestState::ACTIVE;
				q.list[0]->objectiveState = Enums::QuestState::ACTIVE;
				q.list[1]->objectiveState = Enums::QuestState::ACTIVE;
			}

			TEST_METHOD(ListObjectiveActivateActivatesListOfObjective)
			{
				q.list[0]->objectiveState = Enums::QuestState::NOT_ACTIVE;
				q.list[1]->objectiveState = Enums::QuestState::NOT_ACTIVE;

				q.activateObjective();
				Assert::AreEqual<int>((int)q.list[0]->objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<int>((int)q.list[1]->objectiveState, (int)Enums::QuestState::ACTIVE);

			}

			TEST_METHOD(ListObjectiveActiveOnFirstObjectiveCompleteAndSecondActive)
			{
				q.list[0]->completeObjective();
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<int>((int)q.list[0]->objectiveState, (int)Enums::QuestState::COMPLETE);
				Assert::AreEqual<int>((int)q.list[1]->objectiveState, (int)Enums::QuestState::ACTIVE);
			}
			TEST_METHOD(ListObjectiveFailsOnAnyFailed)
			{
				q.list[0]->failObjective();
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), failed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::FAILED);
				Assert::AreEqual<int>((int)q.list[0]->objectiveState, (int)Enums::QuestState::FAILED);
				Assert::AreEqual<int>((int)q.list[1]->objectiveState, (int)Enums::QuestState::FAILED);
			}

			TEST_METHOD(ListObjectivePendingCompleteOnAllObjectivesPendingComplete)
			{
				q.list[0]->objectiveState = Enums::QuestState::PENDING_COMPLETE;
				q.list[1]->objectiveState = Enums::QuestState::PENDING_COMPLETE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
				Assert::AreEqual<int>((int)q.list[0]->objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
				Assert::AreEqual<int>((int)q.list[1]->objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
			}
			TEST_METHOD(ListObjectivePendingCompleteOnAllButOneCompleteAndLastIsPendingComplete)
			{
				q.list[0]->objectiveState = Enums::QuestState::COMPLETE;
				q.list[1]->objectiveState = Enums::QuestState::PENDING_COMPLETE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
				Assert::AreEqual<int>((int)q.list[0]->objectiveState, (int)Enums::QuestState::COMPLETE);
				Assert::AreEqual<int>((int)q.list[1]->objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
			}
			TEST_METHOD(ListObjectivePendingFailureOnAnyObjectivePendingFailure)
			{
				q.list[0]->objectiveState = Enums::QuestState::PENDING_FAILURE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_FAILURE);
				Assert::AreEqual<int>((int)q.list[0]->objectiveState, (int)Enums::QuestState::PENDING_FAILURE);
				Assert::AreEqual<int>((int)q.list[1]->objectiveState, (int)Enums::QuestState::ACTIVE);
			}

			TEST_METHOD(ListObjectiveCompleteOnAllComplete)
			{
				q.list[0]->objectiveState = Enums::QuestState::COMPLETE;
				q.list[1]->objectiveState = Enums::QuestState::COMPLETE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), completed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
				Assert::AreEqual<int>((int)q.list[0]->objectiveState, (int)Enums::QuestState::COMPLETE);
				Assert::AreEqual<int>((int)q.list[1]->objectiveState, (int)Enums::QuestState::COMPLETE);
			}
			TEST_METHOD(ListObjectiveActiveOnPendingFailureResolve)
			{
				q.objectiveState = Enums::QuestState::PENDING_FAILURE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<int>((int)q.list[0]->objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<int>((int)q.list[1]->objectiveState, (int)Enums::QuestState::ACTIVE);
			}

			TEST_METHOD(ListObjectivePendingComplete_CompleteOrFailObjectiveCalled)
			{
				q.objectiveState = Enums::QuestState::PENDING_COMPLETE;
				Assert::AreEqual<size_t>(q.completeOrFailObjective(), completed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
			}
			TEST_METHOD(ListObjectivePendingFailure_CompleteOrFailObjectiveCalled)
			{
				q.objectiveState = Enums::QuestState::PENDING_FAILURE;
				Assert::AreEqual<size_t>(q.completeOrFailObjective(), failed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::FAILED);
			}

		};


		Questing::ListObjective ListQuestObjectiveTest::q;
		size_t ListQuestObjectiveTest::objectiveId = 1;
		size_t ListQuestObjectiveTest::completed_state = 2;
		size_t ListQuestObjectiveTest::failed_state = 3;
	}
}

#endif
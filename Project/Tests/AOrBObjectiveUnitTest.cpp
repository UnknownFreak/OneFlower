#ifdef _UNITTESTS_
#include "CppUnitTest.h"
#include <Tests/TestObjects.hpp>

#include <Object/GameObject.hpp>
#include <Quest/AOrBObjective.hpp>
#include <Tests/TestObjects.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace TQuesting
	{

		TEST_CLASS(AOrBQuestObjectiveTest)
		{

		public:
			
			static Questing::AOrBObjective q;
			static size_t objectiveId;
			static size_t completed_state;
			static size_t failed_state;

			TEST_CLASS_INITIALIZE(Initialize)
			{

				q.objectiveId = objectiveId;
				q.nextQuestObjectiveStateId = completed_state;
				q.failedObjectiveStateId = failed_state;
				q.a = std::make_unique<DummyObjective>();
				q.b = std::make_unique<DummyObjective>();
			}

			TEST_METHOD_INITIALIZE(MethodInit)
			{
				q.objectiveState = Enums::QuestState::ACTIVE;
				q.a->objectiveState = Enums::QuestState::ACTIVE;
				q.b->objectiveState = Enums::QuestState::ACTIVE;
			}

			TEST_METHOD(AOrBObjectiveActivateActivatesAAndBObjective)
			{
				q.a->objectiveState = Enums::QuestState::NOT_ACTIVE;
				q.b->objectiveState = Enums::QuestState::NOT_ACTIVE;

				q.activateObjective();
				Assert::AreEqual<int>((int)q.a->objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<int>((int)q.b->objectiveState, (int)Enums::QuestState::ACTIVE);

			}

			TEST_METHOD(AOrBObjectiveCompleteOnAObjectiveFinished)
			{
				q.a->completeObjective();
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), completed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
				Assert::AreEqual<int>((int)q.a->objectiveState, (int)Enums::QuestState::COMPLETE);
				Assert::AreEqual<int>((int)q.b->objectiveState, (int)Enums::QuestState::FAILED);
			}
			TEST_METHOD(AOrBObjectiveFailseOnBObjectiveFinished)
			{
				q.b->completeObjective();
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), failed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::FAILED);
				Assert::AreEqual<int>((int)q.a->objectiveState, (int)Enums::QuestState::FAILED);
				Assert::AreEqual<int>((int)q.b->objectiveState, (int)Enums::QuestState::COMPLETE);
			}

			TEST_METHOD(AOrBObjectivePendingCompleteOnAObjectivePendingComplete)
			{
				q.a->objectiveState = Enums::QuestState::PENDING_COMPLETE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
				Assert::AreEqual<int>((int)q.a->objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
				Assert::AreEqual<int>((int)q.b->objectiveState, (int)Enums::QuestState::ACTIVE);
			}
			TEST_METHOD(AOrBObjectivePendingCompleteOnBObjectivePendingFailure)
			{
				q.b->objectiveState = Enums::QuestState::PENDING_FAILURE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
				Assert::AreEqual<int>((int)q.a->objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<int>((int)q.b->objectiveState, (int)Enums::QuestState::PENDING_FAILURE);
			}

			TEST_METHOD(AOrBObjectivePendingCompleteOnBObjectivePendingComplete)
			{
				q.b->objectiveState = Enums::QuestState::PENDING_COMPLETE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_FAILURE);
				Assert::AreEqual<int>((int)q.a->objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<int>((int)q.b->objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
			}
			TEST_METHOD(AOrBObjectivePendingCompleteOnAObjectivePendingFailure)
			{
				q.a->objectiveState = Enums::QuestState::PENDING_FAILURE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_FAILURE);
				Assert::AreEqual<int>((int)q.a->objectiveState, (int)Enums::QuestState::PENDING_FAILURE);
				Assert::AreEqual<int>((int)q.b->objectiveState, (int)Enums::QuestState::ACTIVE);
			}

			TEST_METHOD(AOrBObjectivePendingComplete_CompleteOrFailObjectiveCalled)
			{
				q.objectiveState = Enums::QuestState::PENDING_COMPLETE;
				Assert::AreEqual<size_t>(q.completeOrFailObjective(), completed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
			}
			TEST_METHOD(AOrBObjectivePendingFailure_CompleteOrFailObjectiveCalled)
			{
				q.objectiveState = Enums::QuestState::PENDING_FAILURE;
				Assert::AreEqual<size_t>(q.completeOrFailObjective(), failed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::FAILED);
			}

			TEST_METHOD(AOrBObjectivePendingCompleteATakesPreferenceComplete)
			{
				q.a->objectiveState = Enums::QuestState::PENDING_COMPLETE;
				q.b->objectiveState = Enums::QuestState::PENDING_COMPLETE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
				Assert::AreEqual<int>((int)q.a->objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
				Assert::AreEqual<int>((int)q.b->objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
			}
			TEST_METHOD(AOrBObjectivePendingCompleteATakesPreferenceFailure)
			{
				q.a->objectiveState = Enums::QuestState::PENDING_FAILURE;
				q.b->objectiveState = Enums::QuestState::PENDING_FAILURE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(nullptr), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
				Assert::AreEqual<int>((int)q.a->objectiveState, (int)Enums::QuestState::PENDING_FAILURE);
				Assert::AreEqual<int>((int)q.b->objectiveState, (int)Enums::QuestState::PENDING_FAILURE);
			}
		};


		Questing::AOrBObjective AOrBQuestObjectiveTest::q;
		size_t AOrBQuestObjectiveTest::objectiveId = 1;
		size_t AOrBQuestObjectiveTest::completed_state = 2;
		size_t AOrBQuestObjectiveTest::failed_state = 3;
	}
}

#endif
#ifdef _UNITTESTS_
#include "CppUnitTest.h"
#include <Tests/TestObjects.hpp>

#include <Object/GameObject.hpp>
#include <Quest/DuelObjective.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace TQuesting
	{

		TEST_CLASS(DuelQuestObjectiveTest)
		{
		public:

			static GameObject o;
			static GameObject o2;
			static Questing::DuelObjective q;
			static size_t objectiveId;
			static size_t completed_state;
			static size_t failed_state;

			TEST_CLASS_INITIALIZE(Initialize)
			{
				o.id = Core::uuid();
				o.tag = "A";
				o2.id = Core::uuid();
				o2.tag = "B";

				q.objectiveId = objectiveId;
				q.nextQuestObjectiveStateId = completed_state;
				q.failedObjectiveStateId = failed_state;
				q.duel = o.id;
			}

			TEST_METHOD_INITIALIZE(MethodInit)
			{
				q.objectiveState = Enums::QuestState::ACTIVE;
				q.completeOnPendingComplete = false;
			}

			TEST_METHOD(duelObjective_correct_id_dies)
			{
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o), completed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
			}
			TEST_METHOD(duelObjective_incorrect_id_dies)
			{
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o2), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
			}


			TEST_METHOD(duelObjective_correct_id_dies_not_active)
			{
				q.objectiveState = Enums::QuestState::NOT_ACTIVE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
			}
			TEST_METHOD(duelObjective_incorrect_id_dies_not_active)
			{
				q.objectiveState = Enums::QuestState::NOT_ACTIVE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o2), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
			}
			TEST_METHOD(duelObjective_completeOrFailObjective_completes)
			{
				Assert::AreEqual<size_t>(q.completeOrFailObjective(), completed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
			}
		};


		Questing::DuelObjective DuelQuestObjectiveTest::q;
		GameObject DuelQuestObjectiveTest::o;
		GameObject DuelQuestObjectiveTest::o2;
		size_t DuelQuestObjectiveTest::objectiveId = 1;
		size_t DuelQuestObjectiveTest::completed_state = 2;
		size_t DuelQuestObjectiveTest::failed_state = 3;
	}
}

#endif
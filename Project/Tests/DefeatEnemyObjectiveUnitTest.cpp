#ifdef _UNITTESTS_
#include "CppUnitTest.h"

#include <Object/GameObject.hpp>

#include <Quest/DefeatEnemyObjective.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace TQuesting
	{

		TEST_CLASS(DefeatEnemyQuestObjectiveTest)
		{
		public:

			static GameObject o;
			static GameObject o2;
			static GameObject o3;
			static Questing::DefeatEnemyObjective q;
			static size_t objectiveId;
			static size_t completed_state;
			static size_t failed_state;

			TEST_CLASS_INITIALIZE(Initialize)
			{
				o.id = Core::uuid();
				o.tag = "A";
				o2.id = Core::uuid();
				o2.tag = "B";
				o3.id = Core::uuid();
				o3.tag = "C";

				q.objectiveId = objectiveId;
				q.nextQuestObjectiveStateId = completed_state;
				q.failedObjectiveStateId = failed_state;
				q.tag = "A";
				q.enemy = o3.id;
			}

			TEST_METHOD_INITIALIZE(MethodInit)
			{
				q.objectiveState = Enums::QuestState::ACTIVE;
				q.completeOnPendingComplete = false;
				q.currentDefeatCount = 0;
				q.defeatCount = 2;
			}

			TEST_METHOD(defeatEnemy_correct_tag)
			{
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<size_t>(q.currentDefeatCount, size_t(1));
			}
			TEST_METHOD(defeatEnemy_incorrect_tag)
			{
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o2), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<size_t>(q.currentDefeatCount, size_t(0));
			}
			TEST_METHOD(defeatEnemy_correct_id)
			{
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o3), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
				Assert::AreEqual<size_t>(q.currentDefeatCount, size_t(1));
			}

			TEST_METHOD(defeatEnemy_correct_tag_not_active)
			{
				q.objectiveState = Enums::QuestState::NOT_ACTIVE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
				Assert::AreEqual<size_t>(q.currentDefeatCount, size_t(0));
			}
			TEST_METHOD(defeatEnemy_incorrect_tag_not_active)
			{
				q.objectiveState = Enums::QuestState::NOT_ACTIVE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o2), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
				Assert::AreEqual<size_t>(q.currentDefeatCount, size_t(0));
			}
			TEST_METHOD(defeatEnemy_correct_id_not_active)
			{
				q.objectiveState = Enums::QuestState::NOT_ACTIVE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o3), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
				Assert::AreEqual<size_t>(q.currentDefeatCount, size_t(0));
			}

			TEST_METHOD(defeatEnemy_finish_objective_complete_on_pending)
			{
				q.defeatCount = 1;
				q.completeOnPendingComplete = true;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o), completed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
				Assert::AreEqual<size_t>(q.currentDefeatCount, size_t(1));
			}
			TEST_METHOD(defeatEnemy_finish_objective_pending)
			{
				q.defeatCount = 1;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
				Assert::AreEqual<size_t>(q.currentDefeatCount, size_t(1));
			}
		};


		Questing::DefeatEnemyObjective DefeatEnemyQuestObjectiveTest::q;
		GameObject DefeatEnemyQuestObjectiveTest::o;
		GameObject DefeatEnemyQuestObjectiveTest::o2;
		GameObject DefeatEnemyQuestObjectiveTest::o3;
		size_t DefeatEnemyQuestObjectiveTest::objectiveId = 1;
		size_t DefeatEnemyQuestObjectiveTest::completed_state = 2;
		size_t DefeatEnemyQuestObjectiveTest::failed_state = 3;
	}
}

#endif
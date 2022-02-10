#ifdef _UNITTESTS_
#include "CppUnitTest.h"
#include <Tests/TestObjects.hpp>

#include <Object/GameObject.hpp>
#include <Quest/DefendObjective.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace TQuesting
	{

		TEST_CLASS(DefendQuestObjectiveTest)
		{
		public:

			static GameObject o;
			static GameObject o2;
			static GameObject o3;
			static Questing::DefendObjective q;
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
				q.defend = o.id;
				q.completeRequirement = nullptr;
			}

			TEST_METHOD_INITIALIZE(MethodInit)
			{
				q.objectiveState = Enums::QuestState::ACTIVE;
				q.completeOnPendingComplete = false;
			}

			TEST_METHOD(defendObjective_correct_id_dies)
			{
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o), failed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::FAILED);
			}
			TEST_METHOD(defendObjective_incorrect_id_dies)
			{
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o2), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
			}


			TEST_METHOD(defendObjective_correct_id_dies_not_active)
			{
				q.objectiveState = Enums::QuestState::NOT_ACTIVE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
			}
			TEST_METHOD(defendObjective_incorrect_id_dies_not_active)
			{
				q.objectiveState = Enums::QuestState::NOT_ACTIVE;
				Assert::AreEqual<size_t>(q.onEnemyDefeated(&o2), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
			}
			TEST_METHOD(defendObjective_completeOrFailObjective_completes_if_active_no_requirement)
			{
				Assert::AreEqual<size_t>(q.completeOrFailObjective(), completed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
			}
			TEST_METHOD(defendObjective_completeOrFailObjective_completes_if_active_requirement_false)
			{
				q.completeRequirement = std::make_unique<DummyRequirement>(false);
				Assert::AreEqual<size_t>(q.completeOrFailObjective(), objectiveId);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
			}
			TEST_METHOD(defendObjective_completeOrFailObjective_completes_if_active_requirement_true)
			{
				q.completeRequirement = std::make_unique<DummyRequirement>(true);
				Assert::AreEqual<size_t>(q.completeOrFailObjective(), completed_state);
				Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
			}
		};


		Questing::DefendObjective DefendQuestObjectiveTest::q;
		GameObject DefendQuestObjectiveTest::o;
		GameObject DefendQuestObjectiveTest::o2;
		size_t DefendQuestObjectiveTest::objectiveId = 1;
		size_t DefendQuestObjectiveTest::completed_state = 2;
		size_t DefendQuestObjectiveTest::failed_state = 3;
	}
}

#endif
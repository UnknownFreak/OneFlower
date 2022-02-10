#ifdef _UNITTESTS_
#include "CppUnitTest.h"
#include <Tests/TestObjects.hpp>

#include <Items/Item.hpp>

#include <Quest/QuestObjective.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestFramework = Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace TQuesting
	{

	TEST_CLASS(QuestObjectiveTest)
	{
	public:

		static DummyObjective q;
		static size_t objectiveId;
		static size_t completed_state;
		static size_t failed_state;

		TEST_CLASS_INITIALIZE(Initialize)
		{
			q.objectiveId = objectiveId;
			q.nextQuestObjectiveStateId = completed_state;
			q.failedObjectiveStateId = failed_state;
		}

		TEST_METHOD_INITIALIZE(MethodInit)
		{
			q.objectiveState = Enums::QuestState::NOT_ACTIVE;
			q.completeOnPendingComplete = false;
			q.failOnRequirmentUnfulfilled = false;
			q.activationRequirement = nullptr;
		}

		TEST_METHOD(completeObjective)
		{
			Assert::AreEqual<size_t>(q.completeObjective(), completed_state);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
		}
		TEST_METHOD(failObjective)
		{
			Assert::AreEqual<size_t>(q.failObjective(), failed_state);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::FAILED);
		}
		TEST_METHOD(completeOrFailNoPendingState)
		{
			Assert::AreEqual<size_t>(q.completeOrFailObjective(), objectiveId);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
		}
		TEST_METHOD(completeOrFailPendingComplete)
		{
			q.objectiveState = Enums::QuestState::PENDING_COMPLETE;
			Assert::AreEqual<size_t>(q.completeOrFailObjective(), completed_state);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::COMPLETE);
		}
		TEST_METHOD(completeOrFailPendingFailure)
		{
			q.objectiveState = Enums::QuestState::PENDING_FAILURE;
			Assert::AreEqual<size_t>(q.completeOrFailObjective(), failed_state);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::FAILED);
		}

		TEST_METHOD(completeOrFailPendingFailure_force)
		{
			q.objectiveState = Enums::QuestState::ACTIVE;
			Assert::AreEqual<size_t>(q.completeOrFailObjective(true), failed_state);
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::FAILED);
		}

		TEST_METHOD(activateObjective_NoRequirementSet)
		{
			q.activateObjective();
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
		}
		TEST_METHOD(activateObjective_NoRequirementSet_PendingComplete)
		{
			q.objectiveState = Enums::QuestState::PENDING_COMPLETE;
			q.activateObjective();
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
		}
		TEST_METHOD(deactivateObjective_NoRequirementSet)
		{
			q.objectiveState = Enums::QuestState::ACTIVE;
			q.deactivateObjective();
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
		}
		TEST_METHOD(deactivateObjective_NoRequirementSet_PendingComplete)
		{
			q.objectiveState = Enums::QuestState::PENDING_COMPLETE;
			q.deactivateObjective();
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_COMPLETE);
		}

		TEST_METHOD(activationRequirement_fullfilled_activate)
		{
			q.activationRequirement = std::make_unique<DummyRequirement>(true );
			q.activateObjective();
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
		}
		TEST_METHOD(activationRequirement_unfullfilled_activate)
		{
			q.activationRequirement = std::make_unique<DummyRequirement>(false);
			q.activateObjective();
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
		}

		TEST_METHOD(activationRequirement_fullfilled_deactivate)
		{
			q.objectiveState = Enums::QuestState::ACTIVE;
			q.activationRequirement = std::make_unique<DummyRequirement>(true);
			q.deactivateObjective();
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::ACTIVE);
		}
		TEST_METHOD(activationRequirement_unfullfilled_deactivate)
		{
			q.objectiveState = Enums::QuestState::ACTIVE;
			q.activationRequirement = std::make_unique<DummyRequirement>(false);
			q.deactivateObjective();
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
		}
		TEST_METHOD(activationRequirement_unfullfilled_deactivate_failOnRequirementFailed)
		{
			q.objectiveState = Enums::QuestState::ACTIVE;
			q.failOnRequirmentUnfulfilled = true;
			q.activationRequirement = std::make_unique<DummyRequirement>(false);
			q.deactivateObjective();
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_FAILURE);
		}
		TEST_METHOD(activationRequirement_unfullfilled_deactivate_updateObjectiveRequirement)
		{
			q.objectiveState = Enums::QuestState::ACTIVE;
			q.activationRequirement = std::make_unique<DummyRequirement>(false);
			q.updateObjectiveRequirement();
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::NOT_ACTIVE);
		}
		TEST_METHOD(activationRequirement_unfullfilled_deactivate_pendingFailure_updateObjectiveRequirement)
		{
			q.objectiveState = Enums::QuestState::ACTIVE;
			q.failOnRequirmentUnfulfilled = true;
			q.activationRequirement = std::make_unique<DummyRequirement>(false);
			q.updateObjectiveRequirement();
			Assert::AreEqual<int>((int)q.objectiveState, (int)Enums::QuestState::PENDING_FAILURE);
		}
	};

	DummyObjective QuestObjectiveTest::q;
	size_t QuestObjectiveTest::objectiveId = 1;
	size_t QuestObjectiveTest::completed_state = 2;
	size_t QuestObjectiveTest::failed_state = 3;
	}
}

#endif
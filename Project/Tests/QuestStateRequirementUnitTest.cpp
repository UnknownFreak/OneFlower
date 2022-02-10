#ifdef _UNITTESTS_

#include "CppUnitTest.h"

#include <File/SaveFile.hpp>
#include <Requirement/QuestStateRequirement.hpp>
#include <Quest/QuestState.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace TRequirement
	{
		TEST_CLASS(QuestStateRequirementTest)
		{
		public:

			static File::SaveFile* saveFile;
			static Requirement::QuestStateRequirment r;
			static File::Mod::ModFileUUIDHelper existing;
			static File::Mod::ModFileUUIDHelper notExisting;

			TEST_CLASS_INITIALIZE(Initialize)
			{
				existing.name = "Abc";
				notExisting.name = "Abc";
				saveFile = &Engine::GetModule<File::SaveFile>();
				saveFile->setQuestState(existing, Questing::QuestState{ 0, Enums::QuestState::ACTIVE, {{1,{Enums::QuestState::ACTIVE, 0}}} });
			}

			TEST_METHOD_INITIALIZE(methodInitialize)
			{
				r.questState = Enums::QuestState::COMPLETE;
				r.questId = existing;
				r.checkObjective = false;
			}

			TEST_METHOD(TestFullfiledFalseObjectNotExists)
			{
				r.questId = notExisting;
				Assert::IsFalse(r.fullfilled());
			}
			TEST_METHOD(TestFullfiledFalseObjectNoStats)
			{
				r.questId = existing;
				Assert::IsFalse(r.fullfilled());
			}

			TEST_METHOD(TestFullfiledFalseNotSameState)
			{
				r.questId = existing;
				Assert::IsFalse(r.fullfilled());
			}
			TEST_METHOD(TestFullfiledTrue)
			{
				r.questId = existing;
				r.questState = Enums::QuestState::ACTIVE;
				Assert::IsTrue(r.fullfilled());
			}

			TEST_METHOD(TestFullfiledFalseObjectiveNotSameState)
			{
				r.questId = existing;
				r.checkObjective = true;
				r.objectiveId = 1;
				Assert::IsFalse(r.fullfilled());
			}

			TEST_METHOD(TestFullfiledFalseObjectiveNotExists)
			{
				r.questId = existing;
				r.checkObjective = true;
				r.objectiveId = 2121;
				Assert::IsFalse(r.fullfilled());
			}

			TEST_METHOD(TestFullfiledFalseObjectiveNotExistsEnumDefaultConstruct)
			{
				r.questId = existing;
				r.checkObjective = true;
				r.objectiveId = 2121;
				r.questState = Enums::QuestState::NOT_ACTIVE;
				Assert::IsFalse(r.fullfilled());
			}

			TEST_METHOD(TestFullfiledTrueObjectiveSameState)
			{
				r.questId = existing;
				r.checkObjective = true;
				r.objectiveId = 1;
				r.questState = Enums::QuestState::ACTIVE;
				Assert::IsTrue(r.fullfilled());
			}
		};
		File::SaveFile* QuestStateRequirementTest::saveFile = nullptr;
		Requirement::QuestStateRequirment QuestStateRequirementTest::r;
		File::Mod::ModFileUUIDHelper QuestStateRequirementTest::existing;
		File::Mod::ModFileUUIDHelper QuestStateRequirementTest::notExisting;

	}
}

#endif
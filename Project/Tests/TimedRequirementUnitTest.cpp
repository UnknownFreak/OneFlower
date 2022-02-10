#ifdef _UNITTESTS_

#include "CppUnitTest.h"

#include <File/SaveFile.hpp>
#include <Requirement/TimedRequirement.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace TRequirement
	{
		TEST_CLASS(TimedRequirementTest)
		{
		public:

			static File::SaveFile* saveFile;
			static Requirement::TimedRequirement r;
			static ModFileUUIDHelper existing;

			TEST_CLASS_INITIALIZE(Initialize)
			{
				r.timerInfo.currentTime = 0.f;
				r.timerInfo.maxTime = 1.f;
				r.timerInfo.started = false;
				r.timerInfo.finished = false;

				existing.name = "Abc";
				saveFile = &Engine::GetModule<File::SaveFile>();
				saveFile->setTickTimer(existing, r.timerInfo);
			}

			TEST_METHOD_INITIALIZE(methodInitialize)
			{
				r.fullfilledIftimeRanOut = false;
				r.timerId = existing;
				r.timerInfo.currentTime = 0.f;
				r.timerInfo.started = false;
			}

			TEST_METHOD(notStartedTimerReturnsTrueFulfilledIfBoolFlagFalse)
			{
				Assert::IsTrue(r.fullfilled());
			}
			
			TEST_METHOD(notStartedTimerReturnsFalseFulfilledIfBoolFlagTrue)
			{
				r.fullfilledIftimeRanOut = true;
				Assert::IsFalse(r.fullfilled());
			}

			TEST_METHOD(startedTimerReturnsTrueFullfilledIfBoolFlagFalse)
			{
				r.timerInfo.started = true;
				Assert::IsTrue(r.fullfilled());
			}
			TEST_METHOD(startedTimerReturnsFalseFullfilleddIfBoolFlagFalseAndTimeIsExceeded)
			{
				r.timerInfo.currentTime = 11.f;
				r.timerInfo.started = true;
				Assert::IsFalse(r.fullfilled());
			}
			TEST_METHOD(startedTimerReturnsTrueFullfilledIfBoolFlagTrue)
			{
				r.fullfilledIftimeRanOut = true;
				r.timerInfo.started = true;
				Assert::IsFalse(r.fullfilled());
			}
			TEST_METHOD(startedTimerReturnsTrueFullfilleddIfBoolFlagTrueAndTimeIsExceeded)
			{
				r.fullfilledIftimeRanOut = true;
				r.timerInfo.currentTime = 11.f;
				r.timerInfo.started = true;
				Assert::IsTrue(r.fullfilled());
			}

			TEST_METHOD(finishedTimerReturnsTrueFullfilledIfBoolFlagFalse)
			{
				r.timerInfo.finished = true;
				Assert::IsTrue(r.fullfilled());
			}
			TEST_METHOD(finishedTimerReturnsFalseFullfilleddIfBoolFlagFalseAndTimeIsExceeded)
			{
				r.timerInfo.currentTime = 11.f;
				r.timerInfo.finished = true;
				Assert::IsFalse(r.fullfilled());
			}
			TEST_METHOD(finishedTimerReturnsTrueFullfilledIfBoolFlagTrue)
			{
				r.fullfilledIftimeRanOut = true;
				r.timerInfo.finished = true;
				Assert::IsFalse(r.fullfilled());
			}
			TEST_METHOD(finishedTimerReturnsTrueFullfilleddIfBoolFlagTrueAndTimeIsExceeded)
			{
				r.fullfilledIftimeRanOut = true;
				r.timerInfo.currentTime = 11.f;
				r.timerInfo.finished = true;
				Assert::IsTrue(r.fullfilled());
			}

		};
		File::SaveFile* TimedRequirementTest::saveFile = nullptr;
		Requirement::TimedRequirement TimedRequirementTest::r;
		ModFileUUIDHelper TimedRequirementTest::existing;

	}
}

#endif
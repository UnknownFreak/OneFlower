#ifdef _UNITTESTS_

#include "CppUnitTest.h"

#include <Object/ObjectInstanceHandler.hpp>
#include <Requirement/HealthTresholdRequirement.hpp>
#include <Combat/Stats.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	namespace TRequirement
	{
		TEST_CLASS(HealthTresholdRequirementTest)
		{
		public:

			static Requirement::HealthTresholdRequirement r;
			static Component::Stats* s;
			static Core::uuid existing;
			static Core::uuid existingNoStats;
			static Core::uuid notExisting;

			TEST_CLASS_INITIALIZE(Initialize)
			{
				auto& i = Engine::GetModule<EngineModule::ObjectInstanceHandler>();
				auto o = i.addObject();
				existing = o->id;
				s = o->addComponent<Component::Stats>();
				existingNoStats = i.addObject()->id;
				r.percentage = 0.5;
				s->mainStat[Enums::Attribute::Health].max = 100;
			}

			TEST_METHOD(TestFullfiledFalseObjectNotExists)
			{
				r.objectId = notExisting;
				Assert::IsFalse(r.fullfilled());
			}
			TEST_METHOD(TestFullfiledFalseObjectNoStats)
			{
				r.objectId = existingNoStats;
				Assert::IsFalse(r.fullfilled());
			}

			TEST_METHOD(TestFullfiledFalseObjectExistsLessThan)
			{
				r.comparitor = Enums::HealthTresholdComparitor::LessThan;
				s->mainStat[Enums::Attribute::Health].current = 100;
				r.objectId = existing;
				Assert::IsFalse(r.fullfilled());
			}
			TEST_METHOD(TestFullfiledFalseObjectExistsMoreThan)
			{
				r.comparitor = Enums::HealthTresholdComparitor::MoreThan;
				s->mainStat[Enums::Attribute::Health].current = 1;
				r.objectId = existing;
				Assert::IsFalse(r.fullfilled());
			}
			TEST_METHOD(TestFullfiledFalseObjectExistsExactlyEqualTo)
			{
				r.comparitor = Enums::HealthTresholdComparitor::ExactlyEqualTo;
				s->mainStat[Enums::Attribute::Health].current = 1;
				r.objectId = existing;
				Assert::IsFalse(r.fullfilled());
			}

			TEST_METHOD(TestFullfiledTrueObjectExistsLessThan)
			{
				r.comparitor = Enums::HealthTresholdComparitor::LessThan;
				s->mainStat[Enums::Attribute::Health].current = 1;
				r.objectId = existing;
				Assert::IsTrue(r.fullfilled());
			}
			TEST_METHOD(TestFullfiledTrueObjectExistsMoreThan)
			{
				r.comparitor = Enums::HealthTresholdComparitor::MoreThan;
				s->mainStat[Enums::Attribute::Health].current = 99;
				r.objectId = existing;
				Assert::IsTrue(r.fullfilled());
			}
			TEST_METHOD(TestFullfiledTrueObjectExistsExactlyEqualTo)
			{
				r.comparitor = Enums::HealthTresholdComparitor::ExactlyEqualTo;
				s->mainStat[Enums::Attribute::Health].current = 50;
				r.objectId = existing;
				Assert::IsTrue(r.fullfilled());
			}
		};
		Requirement::HealthTresholdRequirement HealthTresholdRequirementTest::r;
		Component::Stats* HealthTresholdRequirementTest::s;
		Core::uuid HealthTresholdRequirementTest::existing = Core::uuid();
		Core::uuid HealthTresholdRequirementTest::existingNoStats = Core::uuid();
		Core::uuid HealthTresholdRequirementTest::notExisting = Core::uuid();

	}
}

#endif
#include "HealthTresholdRequirement.hpp"

#include <object/InstanceHandler.hpp>
#include <logger/Logger.hpp>
#include <component/stats.hpp>

namespace Requirement
{

	bool HealthTresholdRequirement::fullfilled()
	{
		auto& x = of::object::get();
		if (x.exists(objectId))
		{
			auto ptr = x.getObject(objectId);
			auto stats = ptr->get<of::component::Stats>();
			if (stats)
			{
				auto p = stats->mainStat[Enums::StatType::Health].current / stats->mainStat[Enums::StatType::Health].max;
				if (comparitor == Enums::HealthTresholdComparitor::LessThan)
					return p < percentage;
				else if (comparitor == Enums::HealthTresholdComparitor::MoreThan)
					return p > percentage;
				else
					return p == percentage;
			}
			else
			{
				auto& logger = of::logger::get().getLogger("Requirement::HealthTresholdRequirement");
				logger.Warning("Checking requirement on an object that does not have any stats! - It will always return false.");
			}
		}
		return false;
	}
	std::unique_ptr<Requirement> HealthTresholdRequirement::clone() const
	{
		return std::make_unique<HealthTresholdRequirement>(*this);
	}
}
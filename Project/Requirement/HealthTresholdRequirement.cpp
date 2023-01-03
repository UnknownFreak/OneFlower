#include "HealthTresholdRequirement.hpp"

#include <module/ObjectInstanceHandler.hpp>
#include <Combat/Stats.hpp>

namespace Requirement
{

	bool HealthTresholdRequirement::fullfilled()
	{
		auto& x = of::engine::GetModule<of::module::ObjectInstanceHandler>();
		if (x.exists(objectId))
		{
			auto ptr = x.getObject(objectId);
			auto stats = ptr->get<of::object::component::Stats>();
			if (stats)
			{
				auto p = stats->mainStat[Enums::Attribute::Health].current / stats->mainStat[Enums::Attribute::Health].max;
				if (comparitor == Enums::HealthTresholdComparitor::LessThan)
					return p < percentage;
				else if (comparitor == Enums::HealthTresholdComparitor::MoreThan)
					return p > percentage;
				else
					return p == percentage;
			}
			else
			{
				auto& logger = of::engine::GetModule<of::module::logger::OneLogger>().getLogger("Requirement::HealthTresholdRequirement");
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
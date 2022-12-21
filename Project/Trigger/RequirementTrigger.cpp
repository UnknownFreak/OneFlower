#include "RequirementTrigger.hpp"

namespace Trigger
{
    void RequirementTrigger::executeInternal()
    {
        if (requirement->fullfilled())
        {
            trigger->execute();
        }
    }
    std::unique_ptr<of::resource::trigger::Trigger> RequirementTrigger::clone() const
    {
        auto p = std::unique_ptr<RequirementTrigger>(new RequirementTrigger);
        p->triggerOnce = triggerOnce;
        p->uuid = uuid;
        p->requirement = requirement->clone();
        p->trigger = trigger->clone();
        return p;
    }
}
#include "Trigger.hpp"

#include <File/SaveFile.hpp>

namespace Trigger
{
	void Trigger::execute()
	{
		if (triggerOnce && of::engine::GetModule<File::SaveFile>().isTriggered(uuid))
			return;

		executeInternal();
		if (triggerOnce)
			of::engine::GetModule<File::SaveFile>().setTriggered(uuid);
	}
}
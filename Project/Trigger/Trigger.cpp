#include "Trigger.hpp"

#include <File/SaveFile.hpp>

namespace Trigger
{
	void Trigger::execute()
	{
		if (triggerOnce && Engine::GetModule<File::SaveFile>().isTriggered(uuid))
			return;

		executeInternal();
		if (triggerOnce)
			Engine::GetModule<File::SaveFile>().setTriggered(uuid);
	}
}
#ifndef UUIDHELPER_HPP
#define UUIDHELPER_HPP

#include <uuid.h>
#include <Core/String.hpp>
#include "EngineModule/IEngineModule.hpp"

namespace Core
{
	class UUIDHelper : public IEngineResource<UUIDHelper>
	{
	public:
		~UUIDHelper();
		UUIDHelper();

		const ResourceType& getType()
		{
			return type;
		}

		uuids::uuid uuid() const;
		uuids::uuid uuid(const Core::String &) const;
	};
}

#endif
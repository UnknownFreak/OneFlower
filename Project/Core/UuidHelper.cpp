#include "UuidHelper.hpp"

ResourceType IEngineResource<Core::UUIDHelper>::type = ResourceType::UUIDHelper;

Core::UUIDHelper::~UUIDHelper()
{
	
}

Core::UUIDHelper::UUIDHelper()
{
}

uuids::uuid Core::UUIDHelper::uuid() const
{
	return uuids::uuid_system_generator{}();
}

uuids::uuid Core::UUIDHelper::uuid(const Core::String & s) const
{
	return uuids::uuid::from_string(s);
}

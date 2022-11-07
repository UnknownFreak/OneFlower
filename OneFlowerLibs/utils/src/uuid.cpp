#include <common/uuid.hpp>

std::mt19937_64 of::common::uuid::engine = std::mt19937_64(std::random_device()());

namespace of::common
{
	uuids::uuid uuid::from_string(const String& str) noexcept
	{
		if (uuids::uuid::is_valid_uuid(str))
		{
			return uuids::uuid::from_string(str).value();
		}
		else
		{
			return uuids::basic_uuid_random_generator<std::mt19937_64>(engine)();
		}
	}

	uuid::uuid() noexcept : m_uuid(uuids::basic_uuid_random_generator<std::mt19937_64>(engine)()) {}
	uuid::uuid(const uuid& uuid) noexcept : m_uuid(uuid.m_uuid) {}
	uuid::uuid(const uuids::uuid& uuid) noexcept : m_uuid(uuid) {}
	uuid::uuid(const uuid&& uuid) noexcept : m_uuid(uuid.m_uuid) {}
	uuid::uuid(const String& str) noexcept : m_uuid(from_string(str)) {}


	uuid uuid::nil() noexcept
	{
		return uuid(uuids::uuid{});
	}

	bool uuid::is_nil() const noexcept
	{
		return m_uuid.is_nil();
	}

	uuid& uuid::operator=(const uuid& uuid)
	{
		m_uuid = uuid.m_uuid;
		return *this;
	}

	std::string uuid::to_string() const
	{
		std::stringstream sstr;
		sstr << uuids::to_string(this->m_uuid);
		return sstr.str();
	}

	bool uuid::operator<(const uuid& right) const noexcept
	{
		return m_uuid < right.m_uuid;
	}

	bool uuid::operator!=(const uuid& right) const noexcept
	{
		return m_uuid != right.m_uuid;
	}

	bool uuid::operator==(const uuid& right) const noexcept
	{
		return m_uuid == right.m_uuid;
	}
}
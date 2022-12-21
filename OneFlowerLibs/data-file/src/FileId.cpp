#include <file/FileId.hpp>

namespace of::file
{
	FileId::FileId() : FileId("", common::uuid::nil()) {}

	FileId::FileId(const common::uuid& uuid) : FileId("", uuid) {};

	FileId::FileId(const common::String& name, const common::uuid& uuid) : name(name), uuid(uuid) {}

	FileId::FileId(const FileId& copy) : FileId(copy.name, copy.uuid) {}

	FileId& FileId::operator=(const FileId& right)
	{
		name = right.name;
		uuid = right.uuid;
		return *this;
	}

	bool FileId::operator<(const FileId& other) const
	{
		return uuid < other.uuid;
	}

	bool FileId::operator==(const FileId& other) const
	{
		return uuid == other.uuid && name == other.name;
	}

	bool FileId::isValid() const
	{
		return !uuid.is_nil() && name != "";
	}

	common::String FileId::operator()(const bool& truncateUuidString) const
	{
		if (truncateUuidString)
		{
			return "[\"" + name + "\"," + common::truncate(uuid.to_string()) + "]";
		}
		return "[\"" + name + "\"," + uuid.to_string() + "]";
	}
}
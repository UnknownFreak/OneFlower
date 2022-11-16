#ifndef FileId_HPP
#define FileId_HPP
#include <common/String.hpp>
#include <common/uuid.hpp>

namespace of::file
{

	struct FileId
	{

		common::String name;
		common::uuid uuid;

		FileId();
		FileId(const common::String& name, const common::uuid& uuid);
		FileId(const FileId& copy);
		FileId& operator=(const FileId& right);

		bool operator<(const FileId& other) const;

		bool operator==(const FileId& other) const;

		bool isValid() const;

		common::String operator()(const bool& truncateUuidString = false) const;

		template <class Archive>
		void save(Archive& saver) const
		{
			saver(name);
			saver(uuid);
		}

		template <class Archive>
		void load(Archive& loader)
		{
			loader(name);
			loader(uuid);
		}
	};
};

namespace std
{
	template <>
	struct hash<of::file::FileId>
	{
		inline std::size_t operator()(of::file::FileId const& helper) const
		{
			return std::hash<of::common::String>()(helper());
		}
	};
}

#endif
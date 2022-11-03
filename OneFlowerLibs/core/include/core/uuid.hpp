#ifndef UUID_HPP
#define UUID_HPP
//#define UUID_SYSTEM_GENERATOR

#include <vector>
#include <random>
#pragma warning(disable: 6001)
#pragma warning(disable: 5246)
#pragma warning(push, 3)
#include <uuid.h>
#pragma warning(pop)
#pragma warning(default: 6001)
#pragma warning(disable: 5246)

#include <core/String.hpp>

namespace OneFlower::Core
{
	class uuid
	{
		static std::mt19937_64 engine;
		uuids::uuid m_uuid;
	
		uuids::uuid from_string(const Core::String& str) noexcept;
	
	public:

		uuid() noexcept;
		uuid(const uuid& uuid) noexcept;
		uuid(const uuids::uuid& uuid) noexcept;
		uuid(const uuid&& uuid) noexcept;
		uuid(const Core::String& str) noexcept;
	
		static uuid nil() noexcept;
		bool is_nil() const noexcept;

		uuid& operator=(const uuid& uuid);
	
		template<class Archive>
		void save(Archive& ar) const
		{
			const size_t length = m_uuid.as_bytes().size();
			const std::byte* data = m_uuid.as_bytes().data();
			for (size_t i = 0; i < length; i++)
				ar(*(data + i));
		}
	
		template<class Archive>
		void load(Archive& ar)
		{
			const size_t length = m_uuid.as_bytes().size();
			std::vector<uint8_t> byte_vec;
			std::uint8_t b;
			for (size_t i = 0; i < length; i++)
			{
				ar(b);
				byte_vec.push_back(b);
			}
			m_uuid = uuids::uuid(byte_vec.begin(), byte_vec.end());
		}
	
		std::string to_string() const;
		bool operator<(const Core::uuid& right) const noexcept;
		bool operator!=(const Core::uuid& right) const noexcept;
		bool operator==(const Core::uuid& right) const noexcept;
	};
}
namespace std
{
	template <>
	struct hash<OneFlower::Core::uuid>
	{
		std::size_t operator()(OneFlower::Core::uuid const& uuid) const
		{
			return std::hash<std::string>()(uuid.to_string());
		}
	};
}
#endif

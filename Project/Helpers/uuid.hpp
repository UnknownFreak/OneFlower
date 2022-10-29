#ifndef UUID_HPP
#define UUID_HPP
//#define UUID_SYSTEM_GENERATOR

#include <Module/Random.hpp>
#include <uuid.h>

#include <Helpers/String.hpp>
#include <vector>

namespace Core
{
	class uuid
	{
		uuids::uuid m_uuid;
	
		inline uuids::uuid from_string(const Core::String& str) noexcept
		{
			if (uuids::uuid::is_valid_uuid(str))
			{
				return uuids::uuid::from_string(str).value();
			}
			else
			{
				return uuids::basic_uuid_random_generator<std::mt19937_64>(EngineModule::RandomGen::engine)();
			}
		}
	
	public:

		inline uuid() noexcept : m_uuid(uuids::basic_uuid_random_generator<std::mt19937_64>(EngineModule::RandomGen::engine)())
		{}
		inline uuid(const uuid& uuid) noexcept : m_uuid(uuid.m_uuid)
		{}
		inline uuid(const uuids::uuid& uuid) noexcept : m_uuid(uuid)
		{}
		inline uuid(const uuid&& uuid) noexcept : m_uuid(uuid.m_uuid)
		{}
		inline uuid(const Core::String& str) noexcept : m_uuid(from_string(str))
		{}
	
		static uuid nil() noexcept
		{
			return uuid(uuids::uuid{});
		}
	
		inline constexpr bool is_nil() const noexcept
		{
			return m_uuid.is_nil();
		}
	
		inline uuid& operator=(const uuid& uuid)
		{
			m_uuid = uuid.m_uuid;
			return *this;
		}
	
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
	
		inline std::string to_string() const
		{
			std::stringstream sstr;
			sstr << uuids::to_string(this->m_uuid);
			return sstr.str();
		}
	
		inline bool operator<(const Core::uuid& right) const noexcept
		{
			return m_uuid < right.m_uuid;
		}
	
		inline bool operator!=(const Core::uuid& right) const noexcept
		{
			return m_uuid != right.m_uuid;
		}
	
		inline bool operator==(const Core::uuid& right) const noexcept
		{
			return m_uuid == right.m_uuid;
		}
	};
}
namespace std
{
	template <>
	struct hash<Core::uuid>
	{
		std::size_t operator()(Core::uuid const& uuid) const
		{
			return std::hash<std::string>()(uuid.to_string());
		}
	};
}
#endif

#ifndef UUID_HPP
#define UUID_HPP
#include <cereal/types/string.hpp>
#include <uuid.h>
#include <Core/String.hpp>
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
				return uuids::uuid_system_generator{}();
		}

	public:
		inline uuid() noexcept : m_uuid(uuids::uuid_system_generator{}())
		{}
		inline uuid(const uuid& uuid) noexcept : m_uuid(uuid.m_uuid)
		{}
		inline uuid(const uuids::uuid& uuid) noexcept : m_uuid(uuid)
		{}
		inline uuid(const uuid&& uuid) noexcept : m_uuid(std::move(uuid.m_uuid))
		{}
		inline uuid(const Core::String& str) noexcept : m_uuid(from_string(str))
		{
		}

		static uuid nil()
		{
			uuids::uuid id; 
			return uuid(id);
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
			ar(uuids::to_string(m_uuid));
		}

		template<class Archive>
		void load(Archive& ar)
		{
			std::string s;
			ar(s);
			m_uuid = from_string(s);
		}

		inline std::string to_string() const
		{
			std::stringstream sstr;
			sstr << this->m_uuid;
			return sstr.str();
		}

		inline std::wstring to_wstring() const
		{
			std::wstringstream sstr;
			sstr << this->m_uuid;
			return sstr.str();
		}

		inline bool operator<(const Core::uuid& right) const noexcept
		{
			return m_uuid < right.m_uuid;
		}

		inline bool operator!=(const Core::uuid& right)const noexcept
		{
			return m_uuid != right.m_uuid;
		}

		inline bool operator==(const Core::uuid& right)const noexcept
		{
			return m_uuid == right.m_uuid;
		}
	};
}

#endif

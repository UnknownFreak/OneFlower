#pragma once

#include <concepts>
#include <utils/common/string.hpp>
#include <utils/concepts/concepts.hpp>

namespace of::messaging
{

	enum class MessageType
	{
		BASIC_BOOL,
		BASIC_INT,
		BASIC_FLOAT,
		BASIC_STRING,
		CUSTOM,
	};

	class Message
	{
	public:

		template<std::derived_from<Message> T>
		inline bool is() const
		{
			const Message& m = T();
			if (type == MessageType::CUSTOM)
			{
				return m.type == type && m.customId == customId;
			}
			return m.type == type;
		}

		template<std::derived_from<Message> T>
		inline const T& as() const
		{
			return (const T&)*this;
		}

		inline virtual of::common::String toString() const
		{
			return "Type: " + std::to_string((unsigned)type) + ", customId: " + std::to_string(customId);
		}

	protected:

		constexpr Message(const MessageType& type, const unsigned int& customId) : type(type), customId(customId)
		{
		}

		virtual ~Message() = 0 {};

		struct MessageTypeHelper
		{
			template<class T>
			static constexpr MessageType GetBasicType()
			{
				if constexpr(std::same_as<T, bool>)
				{
					return MessageType::BASIC_BOOL;
				}
				else if constexpr(std::signed_integral<T> || std::unsigned_integral<T>)
				{
					return MessageType::BASIC_INT;
				}
				else if constexpr (std::floating_point<T>)
				{
					return MessageType::BASIC_FLOAT;
				}
				else if constexpr (std::same_as<of::common::String, T>)
				{
					return MessageType::BASIC_STRING;
				}
				else
				{
					return MessageType::CUSTOM;
				}
			}

			template<class T>
			static constexpr unsigned int GetBasicTypeId()
			{
				if constexpr (std::same_as<T, bool>)
				{
					return 0;
				}
				else if constexpr (std::signed_integral<T> || std::unsigned_integral<T>)
				{
					return 0;
				}
				else if constexpr (std::floating_point<T>)
				{
					return 0;
				}
				else if constexpr (std::same_as<of::common::String, T>)
				{
					return 0;
				}
				else if constexpr (of::utils::concepts::hasMessageTypeId<T>)
				{
					return T::customMessageId;
				}
				else
				{
					[] <bool flag = false>()
					{
						static_assert(flag, "BasicMessage cannot generate an id for T, derive from BasicMessage directly and call it's protected constructor with a custom id set!");
						static_assert(flag, "OR createa a 'static constexpr unsigned int customMessageId = x' set, to be able to create a BasicMessage<T>(const T& t) instance");
					}();
				}
			}
		};

	private:

		const MessageType type;
		const unsigned int customId;

	};
}
#pragma once

#include <memory>
#include <courier/messageType.hpp>

namespace of::courier
{


	class Message
	{
	public:

		Message();
		Message(const MessageType type);

		template<class T>
		Message(const MessageType type, T&& val) : msgType(type), m_arg(std::make_shared<Arg<T>>(val))
		{
		}

		template<class T>
		Message(const MessageType type, const T&& val) : msgType(type), m_arg(std::make_shared<Arg<T>>(val))
		{

		}

		Message(const Message& other);
		Message& operator=(const Message& other);

		MessageType msgType;


		template<class T>
		void set(T&& value)
		{
			m_arg = std::make_shared<Arg<T>>(value);
		}

		template<class T>
		T get() const
		{
			if (m_arg.operator bool())
			{
				Arg<T>* p = static_cast<Arg<T>*>(m_arg.get());
				return p->t;
			}
			return T();
		}

	private:

		struct ArgBase
		{
			virtual ~ArgBase() = default;
		};
		template<class T>
		struct Arg : public ArgBase
		{
			Arg(T&& arg) : t(arg) {}
			T t;
		};

		std::shared_ptr<ArgBase> m_arg;
	};
}
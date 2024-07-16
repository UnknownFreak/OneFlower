#pragma once

#include <memory>

namespace of::utils::lifetime
{

	class IsAlive
	{
	protected:

		IsAlive() : m_isAlive(std::make_shared<bool>(true))
		{
		}

		~IsAlive()
		{
			*m_isAlive = false;
		}

	public:
		std::weak_ptr<bool> isAlive()
		{
			return m_isAlive;
		}

	private:

		std::shared_ptr<bool> m_isAlive;
	};

}
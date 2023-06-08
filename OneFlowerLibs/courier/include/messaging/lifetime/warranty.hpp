#pragma once

#include <memory>

namespace of::messaging::lifetime
{

	class Warranty
	{
		friend class LifetimeWarranty;
	public:

		bool isValid() const
		{
			return *isAlive;
		}

		explicit operator bool() const
		{
			return *isAlive;
		}

	private:

		Warranty(std::shared_ptr<bool> ptr) : isAlive(ptr)
		{
		}

		std::shared_ptr<bool> isAlive;
	};
}
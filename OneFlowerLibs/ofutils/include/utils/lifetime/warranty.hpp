#pragma once

#include <memory>

namespace of::utils::lifetime
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

		static Warranty makeInvalid()
		{
			return Warranty();
		}

	private:

		Warranty() : isAlive(std::make_shared<bool>(false))
		{

		}

		Warranty(std::shared_ptr<bool> ptr) : isAlive(ptr)
		{
		}

		std::shared_ptr<bool> isAlive;
	};
}
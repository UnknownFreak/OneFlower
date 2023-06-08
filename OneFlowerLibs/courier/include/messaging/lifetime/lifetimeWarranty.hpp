#pragma once

#include <memory>
#include "warranty.hpp"

namespace of::messaging::lifetime
{

	class LifetimeWarranty
	{
	protected:

		LifetimeWarranty() : isAlive(std::make_shared<bool>(true))
		{
		}

		~LifetimeWarranty()
		{
			*isAlive = false;
		}

		Warranty warrantyFromThis()
		{
			return Warranty(isAlive);
		}

	private:

		std::shared_ptr<bool> isAlive;
	};

}
#ifndef IUpdateable_HPP
#define IUPdateable_HPP
#pragma once

namespace Interfaces
{
	struct IUpdateable
	{
		virtual void Update() = 0;
		virtual ~IUpdateable() = default;
	};
}

#endif
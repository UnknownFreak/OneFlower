#ifndef IUpdateable_HPP
#define IUPdateable_HPP

struct IUpdateable
{
	virtual void Update() = 0;
	virtual ~IUpdateable() = default;
};

#endif
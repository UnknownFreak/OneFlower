#ifndef IPatch_HPP
#define IPatch_HPP

namespace Interfaces
{

class IPatch
{

public:
	
	IPatch() = default;
	virtual ~IPatch() = default;

	virtual void Patch(const IPatch& other) = 0;

};
}

#endif
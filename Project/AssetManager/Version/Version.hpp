#ifndef VERSION_HPP
#define VERSION_HPP
#include <Core\String.hpp>

class OneVersion
{
	const unsigned long long version() const;
	unsigned short major;
	unsigned short minor;
	unsigned int revision;

public:
	static OneVersion getCurrentVersion();

	OneVersion();
	OneVersion(unsigned short major, unsigned short minor, unsigned int revision);
	OneVersion(const OneVersion& copy);
	OneVersion& operator=(const OneVersion& right);


	template<class T>
	void serialize(T& archive)
	{
		archive(major);
		archive(minor);
		archive(revision);
	}

	//compare
	bool operator <(const OneVersion& right) const;
	bool operator >(const OneVersion& right) const;
	bool operator <=(const OneVersion& right) const;
	bool operator >=(const OneVersion& right) const;
	bool operator !=(const OneVersion& right) const;
	bool operator == (const OneVersion& right) const;
	
	void incRev();

	Core::String str();

};

#endif
#ifndef VERSION_HPP
#define VERSION_HPP
#include <Core\String.hpp>

struct o_Version
{
	o_Version(unsigned short*& major, unsigned short*& minor, unsigned int*& revision);
	unsigned int revision;
	unsigned short minor;
	unsigned short major;
};

//takes size of ulonglong (64bit)
union UVersion
{
	UVersion(unsigned short*& major, unsigned short*& minor, unsigned int*& revision);
	o_Version _version;
	unsigned long long version;
};

class OneVersion
{
	UVersion version;
	unsigned short* major;
	unsigned short* minor;
	unsigned int* revision;

public:
	static OneVersion getCurrentVersion();

	OneVersion();
	OneVersion(unsigned short major, unsigned short minor, unsigned int revision);

	template<class T>
	void serialize(T& archive)
	{
		archive(*major);
		archive(*minor);
		archive(*revision);
	}

	//compare
	bool operator <(const OneVersion& right) const;
	bool operator >(const OneVersion& right) const;
	bool operator <=(const OneVersion& right) const;
	bool operator >=(const OneVersion& right) const;
	bool operator !=(const OneVersion& right) const;
	bool operator == (const OneVersion& right) const;
	
	void incRev() const;

	Core::String str();

};

#endif
#ifndef VERSION_HPP
#define VERSION_HPP

#include "string.hpp"

class OneVersion
{

	unsigned long long version() const;
	unsigned short major;
	unsigned short minor;
	unsigned short build;
	unsigned short revision;

public:
	static OneVersion getCurrentVersion();

	OneVersion();
	OneVersion(unsigned short major, unsigned short minor, unsigned short build, unsigned short revision);
	OneVersion(unsigned short major, unsigned short minor, unsigned short build);
	OneVersion(const OneVersion& copy);
	OneVersion& operator=(const OneVersion& right);


	template<class T>
	void save(T& archive) const
	{
		archive(major);
		archive(minor);
		archive(build);
		archive(revision);
	}

	template <class T>
	void load(T& ar)
	{
		ar(major);
		ar(minor);
		ar(build);
		ar(revision);
	}

	bool operator <(const OneVersion& right) const;
	bool operator >(const OneVersion& right) const;
	bool operator <=(const OneVersion& right) const;
	bool operator >=(const OneVersion& right) const;
	bool operator !=(const OneVersion& right) const;
	bool operator == (const OneVersion& right) const;
	
	void incRev();

	of::common::String str() const;

	static OneVersion EMPTY;
};

#endif
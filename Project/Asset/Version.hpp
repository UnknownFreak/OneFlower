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
	static const OneVersion getCurrentVersion();

	OneVersion();
	OneVersion(unsigned short major, unsigned short minor, unsigned int revision);
	OneVersion(const OneVersion& copy);
	OneVersion& operator=(const OneVersion& right);


	template<class T>
	void save(T& archive) const
	{
		archive(major);
		archive(minor);
		archive(revision);
	}

	template <class T>
	void load(T& ar)
	{
		ar(major);
		ar(minor);
		ar(revision);
	}

	bool operator <(const OneVersion& right) const;
	bool operator >(const OneVersion& right) const;
	bool operator <=(const OneVersion& right) const;
	bool operator >=(const OneVersion& right) const;
	bool operator !=(const OneVersion& right) const;
	bool operator == (const OneVersion& right) const;
	
	void incRev();

	const Core::String str() const;

	static const OneVersion EMPTY;
};

#endif
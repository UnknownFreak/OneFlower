#include "Version.hpp"

const unsigned long long OneVersion::version() const
{
	return (unsigned __int64(major) << 48) + (unsigned __int64(minor)  << 32) + revision;
}

OneVersion OneVersion::getCurrentVersion()
{
	return OneVersion(1,0,1);
}

OneVersion::OneVersion() :major(0), minor(0), revision(0)
{
}

OneVersion::OneVersion(unsigned short major, unsigned short minor, unsigned int revision) :
	major(major), minor(minor), revision(revision)
{
}

OneVersion::OneVersion(const OneVersion & copy) : major(copy.major), minor(copy.minor), revision(copy.revision)
{
}

OneVersion & OneVersion::operator=(const OneVersion & right)
{
	major = right.major;
	minor = right.minor;
	revision = right.revision;

	return *this;
}

bool OneVersion::operator<(const OneVersion & right) const
{
	return version() < right.version();
}

bool OneVersion::operator>(const OneVersion & right) const
{
	return version() > right.version();
}

bool OneVersion::operator<=(const OneVersion & right) const
{
	return version() <= right.version();
}

bool OneVersion::operator>=(const OneVersion & right) const
{
	return version() >= right.version();
}

bool OneVersion::operator!=(const OneVersion & right) const
{
	return version() != right.version();
}

bool OneVersion::operator==(const OneVersion & right) const
{
	return version() == right.version();
}

void OneVersion::incRev()
{
	revision++;
}

Core::String OneVersion::str()
{
	return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(revision);
}

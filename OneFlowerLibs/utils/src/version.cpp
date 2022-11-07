#include <common/Version.hpp>

OneVersion OneVersion::EMPTY(0, 0, 0);

unsigned long long OneVersion::version() const
{
	return (unsigned __int64(major) << 48) + (unsigned __int64(minor)  << 32) + (unsigned __int64(build) << 15) + revision;
}

OneVersion OneVersion::getCurrentVersion()
{
	return OneVersion(1, 0, 2);
}

OneVersion::OneVersion() :OneVersion(0, 0, 0)
{
}

OneVersion::OneVersion(unsigned short major, unsigned short minor, unsigned short build, unsigned short revision):
	major(major), minor(minor), build(build), revision(revision)

{
}

OneVersion::OneVersion(unsigned short major, unsigned short minor, unsigned short build) : OneVersion(major, minor, build, 0)
{
}

OneVersion::OneVersion(const OneVersion & copy) : major(copy.major), minor(copy.minor), build(copy.build), revision(copy.revision)
{
}

OneVersion & OneVersion::operator=(const OneVersion & right)
{
	major = right.major;
	minor = right.minor;
	build = right.build;
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

of::common::String OneVersion::str() const
{
	auto s = std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(build);
	if (revision)
		s += "." + std::to_string(revision);
	return s;
}

#include "Version.hpp"

OneVersion OneVersion::getCurrentVersion()
{
	return OneVersion(1,0,1);
}

OneVersion::OneVersion() :
	version(this->major, this->minor, this->revision)
{
	*this->major = 0;
	*this->minor = 0;
	*this->revision = 0;
}

OneVersion::OneVersion(unsigned short major, unsigned short minor, unsigned int revision) :
	//We shall reference our own members here
	version(this->major, this->minor, this->revision)
{
	*this->major = major;
	*this->minor = minor;
	*this->revision = revision;
}

// all compare functions compare against our union,
bool OneVersion::operator<(const OneVersion & right) const
{
	return version.version < right.version.version;
}

bool OneVersion::operator>(const OneVersion & right) const
{
	return version.version > right.version.version;
}

bool OneVersion::operator<=(const OneVersion & right) const
{
	return version.version <= right.version.version;
}

bool OneVersion::operator>=(const OneVersion & right) const
{
	return version.version >= right.version.version;
}

bool OneVersion::operator!=(const OneVersion & right) const
{
	return version.version != right.version.version;
}

bool OneVersion::operator==(const OneVersion & right) const
{
	return version.version == right.version.version;
}

void OneVersion::incRev() const
{
	(*revision)++;
}

Core::String OneVersion::c_str()
{
	return std::to_string(*major) + "." + std::to_string(*minor) + "." + std::to_string(*revision);
}

UVersion::UVersion(unsigned short*&  major, unsigned short*& minor, unsigned int*& revision) : _version(major, minor, revision)  
{
}

o_Version::o_Version(unsigned short*& major, unsigned short*&  minor, unsigned int*& revision)
{
	major = &this->major;
	minor = &this->minor;
	revision = &this->revision;
}

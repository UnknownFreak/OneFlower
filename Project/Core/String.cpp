#include "String.hpp"


ResourceType IEngineResource < Core::StringConverter >::type = ResourceType::StringConverter;

Core::StringConverter::StringConverter() : con(new std::wstring_convert<utf8_16converter, wchar_t>())
{
}

Core::StringConverter::~StringConverter()
{
	delete con;
}

std::string Core::StringConverter::toUtf8(std::wstring & wstr)
{
	return con->to_bytes(wstr);
}

std::wstring Core::StringConverter::toUtf16(std::string & str)
{
	return con->from_bytes(str);
}

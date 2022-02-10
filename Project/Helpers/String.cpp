#include "String.hpp"

Enums::EngineResourceType Interfaces::IEngineResource < Core::StringConverter >::type = Enums::EngineResourceType::StringConverter;

Core::StringConverter::StringConverter() : con(new std::wstring_convert<utf8_16converter, wchar_t>())
{
}

Core::StringConverter::StringConverter(const StringConverter& copy) : con(std::move(copy.con))
{
}

Core::StringConverter::~StringConverter()
{
	delete con;
}

Core::String Core::StringConverter::toUtf8(const std::wstring & wstr) const
{
	return con->to_bytes(wstr);
}

std::wstring Core::StringConverter::toUtf16(const Core::String & str) const
{
	return con->from_bytes(str);
}
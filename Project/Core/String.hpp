#ifndef String_HPP
#define String_HPP

#include <string>
#include <ostream>
#include <codecvt>
namespace Core
{
	class StringConverter
	{
		typedef std::codecvt_utf8_utf16<wchar_t> utf8_16converter;
		std::wstring_convert<utf8_16converter, wchar_t>* con;
		
	public:
		StringConverter();
		void deconstruct();
		std::string toUtf8(std::wstring& wstr);
		std::wstring toUtf16(std::string& str);
	};

	extern StringConverter Converter;
	
	typedef std::string String;
	//typedef std::basic_string<char32_t> WString;


}
#endif
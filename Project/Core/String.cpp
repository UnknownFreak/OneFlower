#include "String.hpp"
#include <string>
#include <ostream>
//Core::String::String() : str()
//{
//}
//
//Core::String::String(const String & copy) : str(copy.str)
//{
//}
//
//Core::String::String(const std::string & copy)
//{
//	for each(const char& ch in copy)
//		str.push_back(ch);
//}
//
//Core::String::String(const char * copy) :str()
//{
//	for (copy; *copy != '\0'; copy++)
//		str.push_back(*copy);
//}
//
//Core::String::String(const char16_t * characters) : str(characters)
//{
//}
//
//Core::String::String(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right) : str(_Right)
//{
//}
//
//bool Core::String::empty() const
//{
//	return str.empty();
//}
//
//const char* Core::String::c_str() const
//{
//	const char16_t* pch= str.c_str();
//	std::string _str;
//	for (pch; *pch != '\0'; pch++)
//		_str.push_back(char(*pch));
//	return _str.c_str();
//}
//
//const char16_t * Core::String::data() const
//{
//	return str.data();
//}
//
//std::_String_iterator<std::_String_val<std::_Simple_types<char16_t>>> Core::String::begin()
//{
//	return str.begin();
//}
//
//std::_String_const_iterator<std::_String_val<std::_Simple_types<char16_t>>> Core::String::begin() const
//{
//	return str.begin();
//}
//
//std::_String_iterator<std::_String_val<std::_Simple_types<char16_t>>> Core::String::end()
//{
//	return str.end();
//}
//
//std::_String_const_iterator<std::_String_val<std::_Simple_types<char16_t>>> Core::String::end() const
//{
//	return str.end();
//}
//
//size_t Core::String::find(char _Ch, size_t _Off) const
//{
//	return str.find(_Ch, _Off);
//}
//
//size_t Core::String::find(const char * _Ptr, size_t _Off) const
//{
//	String _str(_Ptr);
//	return str.find(_str.data(), _Off);
//}
//
//size_t Core::String::find(const char * _Ptr, size_t _Off, size_t _Count) const
//{
//	String _str(_Ptr);
//	return str.find(_str.data(), _Off, _Count);
//}
//
//size_t Core::String::find(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& _Right, size_t _Off) const
//{
//	String _str(_Right);
//	return str.find(_str, _Off);
//}
//
//size_t Core::String::find(char16_t _Ch, size_t _Off) const
//{
//	return str.find(_Ch,_Off);
//}
//
//size_t Core::String::find(const char16_t * _Ptr, size_t _Off) const
//{
//	return str.find(_Ptr, _Off);
//}
//
//size_t Core::String::find(const char16_t * _Ptr, size_t _Off, size_t _Count) const
//{
//	return str.find(_Ptr, _Off, _Count);
//}
//
//size_t Core::String::find(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right, size_t _Off) const
//{
//	return str.find(_Right, _Off);
//}
//
//size_t Core::String::find_first_of(char _Ch, size_t _Off) const
//{
//	return str.find_first_of(_Ch, _Off);
//}
//
//size_t Core::String::find_first_of(const char * _Ptr, size_t _Off) const
//{
//	String _str(_Ptr);
//	return str.find_first_of(_str.data(), _Off);
//}
//
//size_t Core::String::find_first_of(const char * _Ptr, size_t _Off, size_t _Count) const
//{
//	String _str(_Ptr);
//	return str.find_first_of(_str.data(), _Off, _Count);
//}
//
//size_t Core::String::find_first_of(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& _Right, size_t _Off) const
//{
//	String _str(_Right);
//	return str.find_first_of(_str, _Off);
//}
//
//size_t Core::String::find_first_of(char16_t _Ch, size_t _Off) const
//{
//	return str.find_first_of(_Ch, _Off);
//}
//
//size_t Core::String::find_first_of(const char16_t * _Ptr, size_t _Off) const
//{
//	return str.find_first_of(_Ptr,_Off);
//}
//
//size_t Core::String::find_first_of(const char16_t * _Ptr, size_t _Off, size_t _Count) const
//{
//	return str.find_first_of(_Ptr, _Off, _Count);
//}
//
//size_t Core::String::find_first_of(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right, size_t _Off) const
//{
//	return str.find_first_of(_Right, _Off);
//}
//
//size_t Core::String::find_first_not_of(char _Ch, size_t _Off) const
//{
//	return str.find_first_not_of(_Ch, _Off);
//}
//
//size_t Core::String::find_first_not_of(const char * _Ptr, size_t _Off) const
//{
//	String _str(_Ptr);
//	return str.find_first_not_of(_str.data(), _Off);
//}
//
//size_t Core::String::find_first_not_of(const char * _Ptr, size_t _Off, size_t _Count) const
//{
//	String _str(_Ptr);
//	return str.find_first_not_of(_str.data(), _Off, _Count);
//}
//
//size_t Core::String::find_first_not_of(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& _Right, size_t _Off) const
//{
//	String _str(_Right);
//	return str.find_first_not_of(_str, _Off);
//}
//
//size_t Core::String::find_first_not_of(char16_t _Ch, size_t _Off) const
//{
//	return str.find_first_not_of(_Ch, _Off);
//}
//
//size_t Core::String::find_first_not_of(const char16_t * _Ptr, size_t _Off) const
//{
//	return str.find_first_not_of(_Ptr, _Off);
//}
//
//size_t Core::String::find_first_not_of(const char16_t * _Ptr, size_t _Off, size_t _Count) const
//{
//	return str.find_first_not_of(_Ptr, _Off, _Count);
//}
//
//size_t Core::String::find_first_not_of(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right, size_t _Off) const
//{
//	return str.find_first_not_of(_Right, _Off);
//}
//
//size_t Core::String::find_last_of(char _Ch, size_t _Off) const
//{
//	return str.find_last_of(_Ch, _Off);
//}
//
//size_t Core::String::find_last_of(const char * _Ptr, size_t _Off) const
//{
//	String _str(_Ptr);
//	return str.find_last_of(_str.data(), _Off);
//}
//
//size_t Core::String::find_last_of(const char * _Ptr, size_t _Off, size_t _Count) const
//{
//	String _str(_Ptr);
//	return str.find_last_of(_str.data(), _Off, _Count);
//}
//
//size_t Core::String::find_last_of(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& _Right, size_t _Off) const
//{
//	String _str(_Right);
//	return str.find_last_of(_str, _Off);
//}
//
//size_t Core::String::find_last_of(char16_t _Ch, size_t _Off) const
//{
//	return str.find_last_of(_Ch, _Off);
//}
//
//size_t Core::String::find_last_of(const char16_t * _Ptr, size_t _Off) const
//{
//	return str.find_last_of(_Ptr, _Off);
//}
//
//size_t Core::String::find_last_of(const char16_t * _Ptr, size_t _Off, size_t _Count) const
//{
//	return str.find_last_of(_Ptr, _Off, _Count);
//}
//
//size_t Core::String::find_last_of(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right, size_t _Off) const
//{
//	return str.find_last_of(_Right, _Off);
//}
//
//size_t Core::String::find_last_not_of(char _Ch, size_t _Off) const
//{
//	return str.find_last_not_of(_Ch, _Off);
//}
//
//size_t Core::String::find_last_not_of(const char * _Ptr, size_t _Off) const
//{
//	String _str(_Ptr);
//	return str.find_last_not_of(_str.data(), _Off);
//}
//
//size_t Core::String::find_last_not_of(const char * _Ptr, size_t _Off, size_t _Count) const
//{
//	String _str(_Ptr);
//	return str.find_last_not_of(_str.data(), _Off, _Count);
//}
//
//size_t Core::String::find_last_not_of(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& _Right, size_t _Off) const
//{
//	String _str(_Right);
//	return str.find_last_not_of(_str, _Off);
//}
//
//size_t Core::String::find_last_not_of(char16_t _Ch, size_t _Off) const
//{
//	return str.find_last_not_of(_Ch, _Off);
//}
//
//size_t Core::String::find_last_not_of(const char16_t * _Ptr, size_t _Off) const
//{
//	return str.find_last_not_of(_Ptr, _Off);
//}
//
//size_t Core::String::find_last_not_of(const char16_t * _Ptr, size_t _Off, size_t _Count) const
//{
//	return str.find_last_not_of(_Ptr, _Off, _Count);
//}
//
//size_t Core::String::find_last_not_of(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right, size_t _Off) const
//{
//	return str.find_last_not_of(_Right, _Off);
//}
//
//size_t Core::String::rfind(char _Ch, size_t _Off) const
//{
//	return str.rfind(_Ch, _Off);
//}
//
//size_t Core::String::rfind(const char * _Ptr, size_t _Off) const
//{
//	String _str(_Ptr);
//	return str.rfind(_str.data(), _Off);
//}
//
//size_t Core::String::rfind(const char * _Ptr, size_t _Off, size_t _Count) const
//{
//	String _str(_Ptr);
//	return str.rfind(_str.data(), _Off, _Count);
//}
//
//size_t Core::String::rfind(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& _Right, size_t _Off) const
//{
//	String _str(_Right);
//	return str.rfind(_str, _Off);
//}
//
//size_t Core::String::rfind(char16_t _Ch, size_t _Off) const
//{
//	return str.rfind(_Ch,_Off);
//}
//
//size_t Core::String::rfind(const char16_t * _Ptr, size_t _Off) const
//{
//	return str.rfind(_Ptr, _Off);
//}
//
//size_t Core::String::rfind(const char16_t * _Ptr, size_t _Off, size_t _Count) const
//{
//	return str.rfind(_Ptr, _Off, _Count);
//}
//
//size_t Core::String::rfind(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right, size_t _Off) const
//{
//	return str.rfind(_Right, _Off);
//}
//
//
//
//std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& Core::String::erase(size_t _Where)
//{
//	return str.erase(_Where);
//}
//
//std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& Core::String::erase(size_t _Off, size_t _Count)
//{
//	return str.erase(_Off, _Count);
//}
//
//std::_String_iterator<std::_String_val<std::_Simple_types<char16_t>>> Core::String::erase(std::_String_const_iterator<std::_String_val<std::_Simple_types<char16_t>>> _First, std::_String_const_iterator<std::_String_val<std::_Simple_types<char16_t>>> _Last)
//{
//	return str.erase(_First, _Last);
//}
//
//std::_String_iterator<std::_String_val<std::_Simple_types<char16_t>>> Core::String::erase(std::_String_const_iterator<std::_String_val<std::_Simple_types<char16_t>>> _Where)
//{
//	return str.erase(_Where);
//}
//
//std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>> Core::String::substr(size_t _Off, size_t _Count) const
//{
//	return str.substr(_Off, _Count);
//}
//
//#ifdef _EDITOR_
//Core::String::String(array<wchar_t>^ ar)
//{
//	for each (char16_t ch in ar)
//		str.push_back(ch);
//}
//#endif
//
//Core::String & Core::String::operator=(const Core::String & copy)
//{
//	str = copy.str;
//	return *this;
//}
//
//Core::String& Core::String::operator=(const std::basic_string<char16_t>& right)
//{
//	str = right;
//	return *this;
//}
//Core::String& Core::String::operator=(const std::basic_string<char>& right)
//{
//	str.clear();
//	for each (char ch in right)
//		str.push_back(ch);
//	return *this;
//}
//
//Core::String & Core::String::operator=(const char * right)
//{
//	str.clear();
//	for (right; *right != '\0'; right++)
//		str.push_back(*right);
//	return *this;
//}
//
//Core::String & Core::String::operator+=(const char16_t * ch)
//{
//	str.append(ch);
//	return *this;
//}
//
//Core::String & Core::String::operator+=(const char* ch)
//{
//	for (ch; *ch != '\0'; ch++)
//		str.push_back(*ch);
//	return *this;
//}
//
//Core::String & Core::String::operator+=(const char16_t& ch)
//{
//	str.push_back(ch);
//	return *this;
//}
//
//Core::String & Core::String::operator+=(const char& ch)
//{
//	str.push_back(ch);
//	return *this;
//}
//
//Core::String::operator std::string() const
//{
//	return std::string(c_str());
//}
//
//Core::String::operator std::u16string() const
//{
//	return str;
//}
//
//Core::String::operator std::wstring() const
//{
//	return std::wstring((wchar_t*)str.data());
//}
//
//std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& Core::String::append(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& append)
//{
//	String _str = append;
//	return str.append(_str.str);
//}
//std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& Core::String::append(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& append)
//{
//	return str.append(append);
//}
//Core::String Core::operator+(const String & left, const char * right)
//{
//	String& leftref = (String&)left;
//	for (right; *right != '\0'; right++)
//		leftref.str.push_back(*right);
//	return left;
//}
//
//Core::String Core::operator+(const String & left, const String & right)
//{
//	return String(left.str + right.str);
//}
//
//Core::String Core::operator+(const char * left, const String & right)
//{
//	Core::String newStr;
//	for (left; *left!= '\0'; left++)
//		newStr.str.push_back(*left);
//	newStr.str.append(right.str);
//	return newStr;
//}
//
//Core::String Core::operator+(const String & left, const std::string & right)
//{
//	return String(left + right.c_str());
//}
//
//bool Core::operator<(const Core::String & left, const Core::String & right)
//{
//	return left.str < right.str;
//}
//
//bool Core::operator>(const Core::String & left, const Core::String & right)
//{
//	return left.str > right.str;
//}
//
//bool Core::operator!=(const Core::String & left, const Core::String & right)
//{
//	return left.str != right.str;
//}
//
//bool Core::operator==(const String & left, const String & right)
//{
//	return left.str == right.str;
//}


//
//std::ostream & Core::operator<<(std::ostream & out, String const & t)
//{
//	for each (char16_t ch in t)
//		out << ch;
//	return out;
//}
//
//std::ostream & Core::operator<<(std::ostream & out, const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& t)
//{
//	out << t;
//	return out;
//}

Core::StringConverter::StringConverter() : con(new std::wstring_convert<utf8_16converter, wchar_t>())
{
}

void Core::StringConverter::free()
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

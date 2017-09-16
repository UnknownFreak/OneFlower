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
		void free();
		std::string toUtf8(std::wstring& wstr);
		std::wstring toUtf16(std::string& str);
	};

	extern StringConverter Converter;
	//Low: make inline

//	class String
//	{
//		std::basic_string<char16_t> str;
//	public:
//		String();
//		String(const String& copy);
//		String(const std::string& copy);
//		String(const char* copy);
//		String(const char16_t* copy);
//		String(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right);
//
//#pragma region WrapperFunctions
//
//		bool empty() const;
//		const char* c_str() const;
//		const char16_t* data() const;
//		std::_String_iterator<std::_String_val<std::_Simple_types<char16_t>>> begin();
//		std::_String_const_iterator<std::_String_val<std::_Simple_types<char16_t>>> begin() const;
//		std::_String_iterator<std::_String_val<std::_Simple_types<char16_t>>> end();
//		std::_String_const_iterator<std::_String_val<std::_Simple_types<char16_t>>> end() const;
//
//		size_t find(char16_t _Ch, size_t _Off = 0) const;
//		size_t find(const char16_t* _Ptr, size_t _Off = 0) const;
//		size_t find(const char16_t* _Ptr, size_t _Off, size_t _Count) const;
//		size_t find(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right, size_t _Off = 0) const;
//
//		size_t find_first_of(char16_t _Ch, size_t _Off = 0) const;
//		size_t find_first_of(const char16_t* _Ptr, size_t _Off = 0) const;
//		size_t find_first_of(const char16_t* _Ptr, size_t _Off, size_t _Count) const;
//		size_t find_first_of(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right, size_t _Off = 0) const;
//
//		size_t find_first_not_of(char16_t _Ch, size_t _Off = 0) const;
//		size_t find_first_not_of(const char16_t* _Ptr, size_t _Off = 0) const;
//		size_t find_first_not_of(const char16_t* _Ptr, size_t _Off, size_t _Count) const;
//		size_t find_first_not_of(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right, size_t _Off = 0) const;
//
//		size_t find_last_of(char16_t _Ch, size_t _Off = 0) const;
//		size_t find_last_of(const char16_t* _Ptr, size_t _Off = 0) const;
//		size_t find_last_of(const char16_t* _Ptr, size_t _Off, size_t _Count) const;
//		size_t find_last_of(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right, size_t _Off = 0) const;
//
//		size_t find_last_not_of(char16_t _Ch, size_t _Off = 0) const;
//		size_t find_last_not_of(const char16_t* _Ptr, size_t _Off = 0) const;
//		size_t find_last_not_of(const char16_t* _Ptr, size_t _Off, size_t _Count) const;
//		size_t find_last_not_of(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right, size_t _Off = 0) const;
//
//		size_t rfind(char16_t _Ch, size_t _Off = 0) const;
//		size_t rfind(const char16_t* _Ptr, size_t _Off = 0) const;
//		size_t rfind(const char16_t* _Ptr, size_t _Off, size_t _Count) const;
//		size_t rfind(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& _Right, size_t _Off = 0) const;
//
//		size_t find(char _Ch, size_t _Off = 0) const;
//		size_t find(const char* _Ptr, size_t _Off = 0) const;
//		size_t find(const char* _Ptr, size_t _Off, size_t _Count) const;
//		size_t find(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& _Right, size_t _Off = 0) const;
//		
//		size_t find_first_of(char _Ch, size_t _Off = 0) const;
//		size_t find_first_of(const char* _Ptr, size_t _Off = 0) const;
//		size_t find_first_of(const char* _Ptr, size_t _Off, size_t _Count) const;
//		size_t find_first_of(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& _Right, size_t _Off = 0) const;
//		
//		size_t find_first_not_of(char _Ch, size_t _Off = 0) const;
//		size_t find_first_not_of(const char* _Ptr, size_t _Off = 0) const;
//		size_t find_first_not_of(const char* _Ptr, size_t _Off, size_t _Count) const;
//		size_t find_first_not_of(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& _Right, size_t _Off = 0) const;
//		
//		size_t find_last_of(char _Ch, size_t _Off = 0) const;
//		size_t find_last_of(const char* _Ptr, size_t _Off = 0) const;
//		size_t find_last_of(const char* _Ptr, size_t _Off, size_t _Count) const;
//		size_t find_last_of(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& _Right, size_t _Off = 0) const;
//		
//		size_t find_last_not_of(char _Ch, size_t _Off = 0) const;
//		size_t find_last_not_of(const char* _Ptr, size_t _Off = 0) const;
//		size_t find_last_not_of(const char* _Ptr, size_t _Off, size_t _Count) const;
//		size_t find_last_not_of(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& _Right, size_t _Off = 0) const;
//		
//		size_t rfind(char _Ch, size_t _Off = 0) const;
//		size_t rfind(const char* _Ptr, size_t _Off = 0) const;
//		size_t rfind(const char* _Ptr, size_t _Off, size_t _Count) const;
//		size_t rfind(const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& _Right, size_t _Off = 0) const;
//
//
//		std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& erase(size_t _Where);
//		std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& erase(size_t _Off, size_t _Count);
//
//		std::_String_iterator<std::_String_val<std::_Simple_types<char16_t>>> erase(std::_String_const_iterator<std::_String_val<std::_Simple_types<char16_t>>> _First, std::_String_const_iterator<std::_String_val<std::_Simple_types<char16_t>>> _Last);
//		std::_String_iterator<std::_String_val<std::_Simple_types<char16_t>>> erase(std::_String_const_iterator<std::_String_val<std::_Simple_types<char16_t>>> _Where);
//
//		std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>> substr(size_t _Off = 0U, size_t _Count = 0) const;
//#pragma endregion
//
//
//#ifdef _EDITOR_
//		String(array<wchar_t>^ ar);
//#endif
//		String& operator=(const Core::String& copy);
//		String& operator=(const std::basic_string<char16_t>& right);
//		String& operator=(const std::basic_string<char>& right);
//		String& operator=(const char *right);
//
//		String& operator+=(const char16_t* ch);
//		String& operator+=(const char* ch);
//
//		String& operator+=(const char16_t& ch);
//		String& operator+=(const char& ch);
//
//		friend String operator+(const String& left, const char* right);
//		friend String operator+(const String& left, const String& right);
//		friend String operator+(const char* left, const String& right);
//		friend String operator+(const String& left, const std::string& right);
//
//		operator std::string() const;
//		operator std::u16string() const;
//		operator std::wstring() const;
//
//		friend bool operator<(const String& left, const String& right);
//		friend bool operator>(const String& left, const String& right);
//		friend bool operator!=(const String& left, const String& right);
//		friend bool operator==(const String& left, const String& right);
//
//		std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& append(const std::basic_string<char, std::char_traits<char>, std::allocator<char >> &);
//		std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& append(const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>> &);
//
//		template<class Archive>
//		void save(Archive& ar) const 
//		{
//			//ar(str.size());
//			//std::basic_string<char16_t>::const_iterator it = str.begin();
//			//std::basic_string<char16_t>::const_iterator eit = str.end();
//			//for each (it; it != eit; it++)
//			//	ar(*it);
//		}
//		template<class Archive>
//		void load(Archive& ar)
//		{
//			//size_t size;
//			//size_t i = 0;
//			//ar(size);
//			//char16_t ch;
//			//for (i; i < size; i++)
//			//{
//			//	ar(ch);
//			//	str.push_back(ch);
//			//}
//		}
//
//	};
	
	//typedef std::basic_ifstream<char16_t> Ifstream;

	//std::ostream & operator<< (std::ostream &out, String const &t);
	//std::ostream & operator<< (std::ostream &out, const std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>>& t);
	typedef std::string String;
	//typedef std::basic_string<char32_t> WString;


}
#endif
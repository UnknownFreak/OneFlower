#ifndef String_HPP
#define String_HPP

#include <iostream>
#include <codecvt>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

#include <Interfaces/IEngineModule.hpp>

namespace Core
{

	typedef std::string String;

#ifdef _WIN32
	const String SEP = "/";
#else
	const String SEP = "/";
#endif

#if defined(_WIN32)
	const String SystemFonts = "C:" + SEP + "Windows" + SEP + "fonts" + SEP;
#elif defined(_APPLE_) && defined(_MACH_)
	const String SystemFonts = SEP + "System" + SEP + "Library" + SEP "Fonts" + SEP;
#else
	const String SystemFonts = SEP + "usr" + SEP + "share" + SEP + "fonts" + SEP;

#endif
	const String dataPath = "Data" + SEP;
	const String savePath = "Save" + SEP;
	const String fontPath = dataPath + "Font" + SEP;
	const String langPath = dataPath + "Lang" + SEP;
	const String texturePath = dataPath + "Textures" + SEP;
	const String soundPath = dataPath + "Sound" + SEP;
	const String modelPath = dataPath + "Model" + SEP;

	const String Builtin = "BUILTIN";

	class StringConverter : public Interfaces::IEngineResource<StringConverter>
	{
		typedef std::codecvt_utf8_utf16<wchar_t> utf8_16converter;
		std::wstring_convert<utf8_16converter, wchar_t>* con;
		
	public:
		
		~StringConverter();
		StringConverter();
		StringConverter(const StringConverter& copy);

 		Enums::EngineResourceType& getType() const
		{
			return type;
		}

		String toUtf8(const std::wstring& wstr) const;
		std::wstring toUtf16(const String& str) const;
	};

	inline String trim(const String& s)
	{
		auto start = s.begin();
		while (start != s.end() && std::isspace(*start, std::locale::classic())) {
			start++;
		}
		auto end = s.end();
		do {
			end--;
		} while (std::distance(start, end) > 0 && std::isspace(*end, std::locale::classic()));

		return String(start, end + 1);
	}

	template<class T>
	inline typename std::enable_if<std::is_same<String, T>::value, String>::type
		toString(const T& value)
	{
		return value;
	}
	template<class T>
	inline typename std::enable_if<!std::is_same<String, T>::value, String>::type
		toString(const T& value)
	{
		return std::to_string(value);
	}

	template <typename T>
	requires std::integral<T>
	Core::String toHex(const T& addr)
	{
		std::stringstream stream;
		stream << "0x"
			<< std::setfill('0') << std::setw(sizeof(T) * 2)
			<< std::hex << addr;

		return stream.str();
	}

	inline Core::String truncate(const Core::String& theString, size_t max_size = 20)
	{
		if (theString.size() > max_size + 3)
		{
			const size_t max_forward = max_size / 2;
			const size_t max_backwards = theString.size() - max_forward;
			Core::String tmp;
			for (size_t i = 0; i < max_forward; i++)
			{
				tmp.push_back(theString[i]);
			}
			tmp += "...";
			for (size_t i = theString.size()-1; i > max_backwards; i--)
			{
				tmp.push_back(theString[i]);
			}
			return tmp;
		}
		return theString;
	}

}
#endif
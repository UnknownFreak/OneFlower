#ifndef String_HPP
#define String_HPP

#include <sstream>
#include <string>
#include <iomanip>

namespace of::common
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

	String trim(const String& s);
	String truncate(const String& theString, size_t max_size = 20);


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
	String toHex(const T& addr)
	{
		std::stringstream stream;
		stream << "0x"
			<< std::setfill('0') << std::setw(sizeof(T) * 2)
			<< std::hex << addr;

		return stream.str();
	}

}

#endif
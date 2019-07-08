#ifndef String_HPP
#define String_HPP

#include <codecvt>
#include <string>

#include "EngineModule\IEngineModule.hpp"



namespace Core
{

	typedef std::string String;

#ifdef _WIN32
	const String SEP = "\\";
#else
	const String SEP = "/";
#endif

	const String dataPath = "Data" + SEP;
	const String fontPath = dataPath + "Font" + SEP;
	const String langPath = dataPath + "Lang" + SEP;
	const String texturePath = dataPath + "Textures" + SEP;
	const String soundPath = dataPath + "Sound" + SEP;
	const String modelPath = dataPath + "Model" + SEP;

	const String Builtin = "BUILTIN";

	class StringConverter : public IEngineResource<StringConverter>
	{
		typedef std::codecvt_utf8_utf16<wchar_t> utf8_16converter;
		std::wstring_convert<utf8_16converter, wchar_t>* con;
		
	public:
		
		~StringConverter();
		StringConverter();

 		const ResourceType& getType()
		{
			return type;
		}

		Core::String toUtf8(const std::wstring& wstr);
		std::wstring toUtf16(const Core::String& str);
	};

	template<class T>
	inline typename std::enable_if<std::is_same<Core::String, T>::value, Core::String>::type
		toString(const T& value)
	{
		return value;
	}
	template<class T>
	inline typename std::enable_if<!std::is_same<Core::String, T>::value, Core::String>::type
		toString(const T& value)
	{
		return std::to_string(value);
	}

}
#endif
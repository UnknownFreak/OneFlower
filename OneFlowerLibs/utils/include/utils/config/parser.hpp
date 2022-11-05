#ifndef Config_HPP
#define Config_HPP

#include <core/String.hpp>
#include <map>
#include <sstream>
#include <fstream>

namespace OneFlower::Config
{
	struct Section
	{

		template <class T>
		std::enable_if_t<std::is_same_v<T, bool>, T>
			to_value_v(const Core::String& v, T )
		{
			if (v == "true" || v == "yes" || v == "on" || v == "1")
				return true;
				return false;
		}

		template <class T>
		std::enable_if_t<!std::is_same_v<T, bool>, T>
			to_value_v(const Core::String& v, T d)
		{
			T t;
			std::stringstream ss(v);
			ss >> t;
			if (ss.fail())
				return d;
			return t;
		}

		std::map<Core::String, Core::String> values;

		Core::String get(const Core::String& key)
		{
			auto value = values.find(key);
			if (value == values.end() || value->first[0] == '#')
				return "";
			return value->second;
		}

		template<class Ty>
		std::enable_if_t<
			!std::is_same_v<Ty, const char*>, Ty>
			get(const Core::String& key, Ty default_value)
		{
			auto str = get(key);
			if (str.size() == 0)
				return default_value;
			Core::String spl = str.substr(0, str.find(";"));
			return to_value_v(spl, default_value);
		}

		template<class Ty>
		std::enable_if_t<std::is_same_v<Ty, const char*>, Core::String>
		get(const Core::String& key, Ty default_value)
		{
			auto str = get(key);
			if (str.size() == 0)
				return default_value;
			return str.substr(0, str.find(";"));
		}

		void putS(const Core::String& key, Core::String value, const Core::String& comment)
		{
			if (comment.size())
				value += "; " + comment;
			values[key] = value;
		}

		template<class Ty>
		std::enable_if_t<
			std::is_same_v<Ty, Core::String> ||
			std::is_same_v<Ty, const char*>
		>
			put(const Core::String& key, Ty value, const Core::String& comment="")
		{
			putS(key, value, comment);
		}
		template<class Ty>
		std::enable_if_t<std::is_same_v<Ty, bool>>
			put(const Core::String& key, Ty value, const Core::String& comment="")
		{
			Core::String s = "false";
			if (value)
				s = "true";
			putS(key, s, comment);
		}
		template<class Ty>
		std::enable_if_t<
			!(std::is_same_v<Ty, bool> ||
			std::is_same_v<Ty, Core::String> ||
			std::is_same_v<Ty, const char*>)>
			put(const Core::String& key, Ty value, const Core::String& comment="")
		{
			putS(key, std::to_string(value), comment);
		}
	};

	class ConfigParser
	{
		Core::String fileName;
		std::map<Core::String, Section> sections;
	public:
		ConfigParser();
		ConfigParser(const Core::String& configFile);


		Section& get(const Core::String& section)
		{
			return sections[section];
		}

		template<class Ty>
		std::enable_if_t<std::is_same_v<Ty, const char*>, Core::String>
		get(const Core::String& section, const Core::String& key, Ty default_value)
		{
			auto the_section = sections.find(section);
			if (the_section == sections.end())
				return default_value;
			return the_section->second.get(key, default_value);
		}

		template<class Ty>
		std::enable_if_t<!std::is_same_v<Ty, const char*>, Ty>
			get(const Core::String& section, const Core::String& key, Ty default_value)
		{
			auto the_section = sections.find(section);
			if (the_section == sections.end())
				return default_value;
			return the_section->second.get(key, default_value);
		}

		template<class Ty>
		void put(const Core::String& section, const Core::String& key, Ty value, const Core::String& comment="")
		{
			sections[section].put<Ty>(key, value, comment);
		}

		void comment(const Core::String& comment);
		void comment(const Core::String& section, const Core::String& comment);
		void clear();
		void load();
		void load(const Core::String& configFile);
		
		void save();
		void save(const Core::String& configFile);

	};

}


#endif
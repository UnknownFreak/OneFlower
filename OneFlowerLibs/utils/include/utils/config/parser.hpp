#ifndef Config_HPP
#define Config_HPP

#include <common/string.hpp>
#include <map>
#include <sstream>
#include <fstream>
#include <functional>

namespace of::config
{
	struct Section
	{

		template <class T>
		std::enable_if_t<std::is_same_v<T, bool>, T>
			to_value_v(const common::String& v, T )
		{
			if (v == "true" || v == "yes" || v == "on" || v == "1")
				return true;
				return false;
		}

		template <class T>
		std::enable_if_t<!std::is_same_v<T, bool>, T>
			to_value_v(const common::String& v, T d)
		{
			T t;
			std::stringstream ss(v);
			ss >> t;
			if (ss.fail())
				return d;
			return t;
		}

		std::map<common::String, common::String> values;

		common::String get(const common::String& key)
		{
			auto value = values.find(key);
			if (value == values.end() || value->first[0] == '#')
				return "";
			return value->second;
		}

		template<class Ty>
		std::enable_if_t<
			!std::is_same_v<Ty, const char*>, Ty>
			get(const common::String& key, Ty default_value)
		{
			auto str = get(key);
			if (str.size() == 0)
				return default_value;
			common::String spl = str.substr(0, str.find(";"));
			return to_value_v(spl, default_value);
		}

		template<class Ty>
		std::enable_if_t<std::is_same_v<Ty, const char*>, common::String>
		get(const common::String& key, Ty default_value)
		{
			auto str = get(key);
			if (str.size() == 0)
				return default_value;
			return str.substr(0, str.find(";"));
		}

		void putS(const common::String& key, common::String value, const common::String& comment)
		{
			if (comment.size())
				value += "; " + comment;
			values[key] = value;
		}

		template<class Ty>
		std::enable_if_t<
			std::is_same_v<Ty, common::String> ||
			std::is_same_v<Ty, const char*>
		>
			put(const common::String& key, Ty value, const common::String& comment="")
		{
			putS(key, value, comment);
		}
		template<class Ty>
		std::enable_if_t<std::is_same_v<Ty, bool>>
			put(const common::String& key, Ty value, const common::String& comment="")
		{
			common::String s = "false";
			if (value)
				s = "true";
			putS(key, s, comment);
		}
		template<class Ty>
		std::enable_if_t<
			!(std::is_same_v<Ty, bool> ||
			std::is_same_v<Ty, common::String> ||
			std::is_same_v<Ty, const char*>)>
			put(const common::String& key, Ty value, const common::String& comment="")
		{
			putS(key, std::to_string(value), comment);
		}
	};

	class ConfigParser
	{
		common::String fileName;
		std::map<common::String, Section> sections;
		static std::function<void(const common::String&, const common::String&, const common::String&)> logger;
	public:
		ConfigParser();
		ConfigParser(const common::String& configFile);


		Section& get(const common::String& section)
		{
			return sections[section];
		}

		template<class Ty>
		std::enable_if_t<std::is_same_v<Ty, const char*>, common::String>
		get(const common::String& section, const common::String& key, Ty default_value)
		{
			auto the_section = sections.find(section);
			if (the_section == sections.end())
				return default_value;
			return the_section->second.get(key, default_value);
		}

		template<class Ty>
		std::enable_if_t<!std::is_same_v<Ty, const char*>, Ty>
			get(const common::String& section, const common::String& key, Ty default_value)
		{
			auto the_section = sections.find(section);
			if (the_section == sections.end())
				return default_value;
			return the_section->second.get(key, default_value);
		}

		template<class Ty>
		void put(const common::String& section, const common::String& key, Ty value, const common::String& comment="")
		{
			sections[section].put<Ty>(key, value, comment);
		}

		void comment(const common::String& comment);
		void comment(const common::String& section, const common::String& comment);
		void clear();
		void load();
		void load(const common::String& configFile);
		
		void save();
		void save(const common::String& configFile);


		/*
		* Sets a logger function that can forward the message to a logger (default logger function is to stdout)
		* 
		* logger function arguments 
		* const common::String& moduleName - if the logger supports logging on a module level pass this as the value for the module
		* const common::String& logLevel - logLevel of the log
		* const common::String& logMessage - the message to be logged
		* 
		* returns void;
		*/
		static void setLogger(std::function<void(const common::String&, const common::String&, const common::String&)> func);

	};

}


#endif
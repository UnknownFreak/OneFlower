#include <utils/config/parser.hpp>

#include <iostream>

std::function<void(const of::common::String&, const of::common::String&, const of::common::String&)> 
of::config::ConfigParser::logger = [](const common::String& module, const common::String& level, const common::String& message)
{
	std::cout << module << " " << level << " " << message << std::endl;
};

namespace of::config
{



	ConfigParser::ConfigParser()
	{
	}

	ConfigParser::ConfigParser(const common::String& configFile)
	{
		load(configFile);
	}

	void ConfigParser::comment(const common::String& comment)
	{
		sections[comment] = {};
	}

	void ConfigParser::comment(const common::String& section, const common::String& comment)
	{
		sections[section].put("#" + comment, "");
	}

	void ConfigParser::clear()
	{
		sections.clear();
	}

	void ConfigParser::load()
	{
		load(fileName);
	}

	void ConfigParser::load(const common::String& configFile)
	{
		fileName = configFile;
		clear();
		std::ifstream file(fileName);
		{
			if (file.is_open())
			{
				logger("ConfigParser", "DEBUG", "Begin parsing configuration file " + fileName);
				common::String section = "";
				common::String line;
				while (std::getline(file, line))
				{
					bool bcomment = false;
					bool bsection = false;
					if (line[0] == '#' || line[0] == ';')
						bcomment = true;
					else if (line[0] == '[' && line[line.size() - 1] == ']')
						bsection = true;

					if (bsection)
					{
						section = line.substr(1, line.size() - 2);
						sections[section] = {};
					}
					else if (section.size())
					{
						if (bcomment)
							comment(section, line.substr(1));
						else
						{
							common::String the_comment = "";
							auto commentpos = line.find_first_of(";");
							if (commentpos != std::string::npos)
								the_comment = line.substr(commentpos);
							else
								commentpos = line.size();
							auto pos = line.find_first_of("=");
							auto key = common::trim(line.substr(0, pos));
							auto value = common::String(line.begin() + pos + 1, line.begin() + commentpos);
							value = common::trim(value);
							put(section, key, value, the_comment);
						}
					}
					else if (section.size() == 0 && bcomment)
						comment(line.substr(1));
				}
				logger("ConfigParser", "DEBUG", "Finished parsing configuration file " + fileName);

			}
			else
			{
				logger("ConfigParser", "WARNING", "Unable to open config file: " + fileName);
			}
		}
		file.close();
	}

	void ConfigParser::save()
	{
		save(fileName);
	}

	void ConfigParser::save(const common::String& configFile)
	{
		fileName = configFile;
		//Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("ConfigParser").Debug("Begin writing configuration file ", fileName);
		std::ofstream file(fileName);
		{
			for (auto& x : sections)
			{
				if (x.first[0] == '#' || x.first[0] == ';')
					file << x.first << std::endl;
				else
				{
					file << "[" << x.first << "]" << std::endl;
					for (auto& y : x.second.values)
					{
						file << y.first;
						if (!(y.first[0] == '#' || y.first[0] == ';'))
							file << " = " << y.second;
						file << std::endl;
					}
				}
			}
		}
		//Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("ConfigParser").Debug("Finished writing configuration file ", fileName);
		file.flush();
		file.close();
	}


	void ConfigParser::setLogger(std::function<void(const common::String&, const common::String&, const common::String&)> inLogger)
	{
		logger = inLogger;
	}

};
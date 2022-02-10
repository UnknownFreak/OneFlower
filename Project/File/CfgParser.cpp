#include "CfgParser.hpp"
#include <Module/Logger/OneLogger.hpp>

File::ConfigParser::ConfigParser()
{
}

File::ConfigParser::ConfigParser(const Core::String& configFile)
{
	load(configFile);
}

void File::ConfigParser::comment(const Core::String& comment)
{
	sections[comment] = {};
}

void File::ConfigParser::comment(const Core::String& section, const Core::String& comment)
{
	sections[section].put("#" + comment, "");
}

void File::ConfigParser::clear()
{
	sections.clear();
}

void File::ConfigParser::load()
{
	load(fileName);
}

void File::ConfigParser::load(const Core::String& configFile)
{
	fileName = configFile;
	clear();
	std::ifstream file(fileName);
	{
		if (file.is_open())
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::ConfigParser").Debug("Begin parsing configuration file", fileName);
			Core::String section = "";
			Core::String line;
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
						Core::String the_comment = "";
						auto commentpos = line.find_first_of(";");
						if (commentpos != std::string::npos)
							the_comment = line.substr(commentpos);
						else
							commentpos = line.size();
						auto pos = line.find_first_of("=");
						auto key = Core::trim(line.substr(0, pos));
						auto value = Core::String(line.begin() + pos + 1, line.begin() + commentpos);
						value = Core::trim(value);
						put(section, key, value, the_comment);
					}
				}
				else if (section.size() == 0 && bcomment)
					comment(line.substr(1));
			}
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::ConfigParser").Debug("Finished parsing configuration file", fileName);
		}
		else
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::ConfigParser").Error("Unable to open config file: ", fileName);
		}
	}
	file.close();
}

void File::ConfigParser::save()
{
	save(fileName);
}

void File::ConfigParser::save(const Core::String& configFile)
{
	fileName = configFile;
	//Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::ConfigParser").Debug("Begin writing configuration file ", fileName);
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
	//Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("File::ConfigParser").Debug("Finished writing configuration file ", fileName);
	file.flush();
	file.close();
}
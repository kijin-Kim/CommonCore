#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

struct Section
{
	std::unordered_map<std::string, std::string> values;
};

class IniFile
{
public:
	std::string GetString(const std::string& section, const std::string& key, const std::string& defaultValue) const
	{
		auto secIt = sections.find(section);
		if (secIt != sections.end())
		{
			auto valIt = secIt->second.values.find(key);
			if (valIt != secIt->second.values.end())
			{
				return valIt->second;
			}
		}
		return defaultValue;
	}

	float GetFloat(const std::string& section, const std::string& key, float defaultValue) const
	{
		std::string valueStr = GetString(section, key, "");
		if (!valueStr.empty())
		{
			return std::stof(valueStr);
		}
		return defaultValue;
	}

	bool GetBool(const std::string& section, const std::string& key, bool defaultValue) const
	{
		std::string valueStr = GetString(section, key, "");
		if (!valueStr.empty())
		{
			return (valueStr == "true" || valueStr == "1");
		}
		return defaultValue;
	}

	int GetInt(const std::string& section, const std::string& key, int defaultValue) const
	{
		std::string valueStr = GetString(section, key, "");
		if (!valueStr.empty())
		{
			return std::stoi(valueStr);
		}
		return defaultValue;
	}

	void SetString(const std::string& section, const std::string& key, const std::string& value)
	{
		sections[section].values[key] = value;
	}

private:
	std::unordered_map<std::string, Section> sections;
};

inline IniFile ParseIniFile(const std::filesystem::path& filePath)
{
	IniFile iniFile;
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		std::cerr << "Can't open file " << filePath.string() << std::endl;
		return iniFile;
	}

	std::string currentSection;
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			continue;
		}

		if (line.front() == '[' && line.back() == ']')
		{
			currentSection = line.substr(1, line.size() - 2);
			continue;
		}

		size_t equalsPos = line.find('=');
		if (equalsPos != std::string::npos)
		{
			std::string key = line.substr(0, equalsPos);
			std::string value = line.substr(equalsPos + 1);
			iniFile.SetString(currentSection, key, value);
		}
	}

	return iniFile;
}
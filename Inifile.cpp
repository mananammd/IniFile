#include "Inifile.h"

IniFile::IniFile(std::string path) {
    std::ifstream file(path);
    try {
	if (!file.is_open()) {
	    throw std::invalid_argument("Error in opening the file");
	}
    }
    catch (std::exception e) {
	std::ofstream fout(path);
	fout.close();
	std::ifstream file(path);
    }

    std::string str;
    std::string section;
    std::string key;
    std::string value;
    while (std::getline(file, str)) {
	if ((str[0] == '[') && (str[str.size() - 1] == ']')) {
	    str.erase(str.size() - 1, 1);
	    str.erase(0, 1);
	    section = str;
	    _data[section];
	}
	else if (str.find("=") != str.npos) {
	    key.insert(0, str, 0, str.find("="));
	    value.insert(0, str, str.find("=") + 1, str.size() - str.find("=") - 1);
	    _data[section][key] = value;
	}
	else {
	    continue;
    	}
	key.clear();
	value.clear();
    }
}

void IniFile::save(std::string path) const {
    std::ofstream file(path);
    for (auto it : _data) {
	file << "[" << it.first << "]" << std::endl;
	for (auto itk : it.second) {
	    file << itk.first << "=" << itk.second << std::endl;
	}
	file << std::endl;
    }
    file.close();
}

template <>
std::string IniFile::read(std::string section, std::string key, std::string defaultValue) const {
    try {
	return _data.at(section).at(key);
    }
    catch (std::exception e) {
	return defaultValue;
    }	
}

template <>
int IniFile::read(std::string section, std::string key, int defaultValue) const {
    try {
	return std::stoi(_data.at(section).at(key));
    }
    catch (std::exception e) {
	return defaultValue;
    }
}

template <>
float IniFile::read(std::string section, std::string key, float defaultValue) const {
    try {
	return std::atof(_data.at(section).at(key).c_str());
    }
    catch (std::exception e) {
	return defaultValue;
    }
}

template <>
bool IniFile::read(std::string section, std::string key, bool defaultValue) const {
    try {
	std::set<std::string> boolValues = {"true", "True", "TRUE",
	"on", "On", "ON", "yes", "Yes", "YES", "y", "Y", "1"};
	std::string value = _data.at(section).at(key);
	if (boolValues.find(value) != boolValues.end()) {
	    return true;
	}
	else {
	    return false;
	}
    }
    catch (std::exception e) {
	return defaultValue;
    }
}

template <>
void IniFile::write(std::string section, std::string key, std::string value) {
    _data[section][key] = value;
}

template <>
void IniFile::write(std::string section, std::string key, int value) {
    _data[section][key] = std::to_string(value);
}

template <>
void IniFile::write(std::string section, std::string key, float value) {
    _data[section][key] = std::to_string(value);
}

template <>
void IniFile::write(std::string section, std::string key, bool value) {
    std::string val;
    (value) ? val = "true" : val = "false";
    _data[section][key] = val;
}

bool IniFile::sectionExists(std::string section) const {
    if (_data.find(section) != _data.end()) {
	return 1;	
    }
    return 0;
}

bool IniFile::keyExists(std::string section, std::string key) const {
    if (sectionExists(section)) {
	if (_data.at(section).find(key) != _data.at(section).end()) {
 	    return 1;
	}
    }
    return 0;
}

std::vector<std::string> IniFile::sections() const {
    std::vector<std::string> sections;
    for (auto it : _data) {
	sections.push_back(it.first);
    }
    return sections;
}

std::vector<std::string> IniFile::keys(std::string section) const {
    std::vector<std::string> key;
    for (auto it : _data.at(section)) {
	key.push_back(it.first);
    }
    return key;
}

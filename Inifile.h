#include <string>
#include <map>
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>
#include <set>

class IniFile {
	std::map<std::string, std::map<std::string, std::string>> _data;

public:
	IniFile(std::string path);

	void save(std::string path) const;

	/**
	 * Считывает из секции section
	 * значение ключа key
	 * Если не удалось считать - возвращает default value
	 *
	 * Определить для std::string, int, float, bool
	 */
	template <typename T>
	T read(std::string section, std::string key, T defaultValue = T{}) const;

	/**
	 * В ключ key из секции section
	 * записывает значение value
	 *
	 * Определить для std::string, int, float, bool
	 */
	template <typename T>
	void write(std::string section, std::string key, T value);

	//Проверяет, существует ли секция section
	bool sectionExists(std::string section) const;

	//Проверяет, существует ли ключ key в секции section
	bool keyExists(std::string section, std::string key) const;
	
	//Возвращает существующие секции
	std::vector<std::string> sections() const;

	//Возвращает существующие ключи в секции section
	std::vector<std::string> keys(std::string section) const;
};
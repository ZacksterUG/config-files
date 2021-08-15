#pragma once
#include <fstream>
#include <vector>

constexpr auto CONFIG_FILE_KEY_NOTEXIST = "-NOTEXIST"; //return this string when you try to read from cfg the key that doesnt exist

class config
{
private:
	std::string FILEPATH; 
public:
	config(std::string file)
	{
		FILEPATH = file;
	}
	config(const char file[])
	{
		FILEPATH = file;
	}
	std::string read(std::string key);
	template <typename T> void write(std::string key, T value);
	void writestr(std::string key, std::string value);
	bool key_exist(std::string key);
};

template<typename T>
inline void config::write(std::string key, T value)
{
	if (!this->key_exist(key))
	{
		std::string buf = key + '=' + std::to_string(value);
		std::fstream File;
		File.open(this->FILEPATH, std::ios::in | std::ios::app | std::ios::out);
		File << buf << std::endl;
		File.close();
	}
	else
	{
		std::vector <std::string> array;
		std::ifstream file(this->FILEPATH);
		std::string buf;
		while (getline(file,buf))
		{
			if (buf.find(key) != -1) buf = key + '=' + std::to_string(value);
			array.push_back(buf);
		}
		file.close();
		std::ofstream in(this->FILEPATH);
		for (int i = 0; i < array.size(); i++) in << array[i] << std::endl;
		in.close();
	}
}

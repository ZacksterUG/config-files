#include <iostream>
#include <string>
#include <fstream>
#include "config.h"

std::string config::read(std::string key) //reading value of the key from cfg
{
	if (!this->key_exist(key)) return CONFIG_FILE_KEY_NOTEXIST;
	std::ifstream File(this->FILEPATH);
	std::string buf;
	while (std::getline(File,buf)) if (buf.find(key) != -1) break;
	File.close();
	return buf.substr(buf.find('=')+1, buf.size() - 1);
}


bool config::key_exist(std::string key) //checks if current key exist
{
	std::ifstream File(this->FILEPATH);
	std::string buf;
	while (std::getline(File,buf))
	{
		if (buf.find(key) != -1)
		{
			File.close();
			return true;
		}
	}
	File.close();
	return false;
}

void config::writestr(std::string key, std::string value) //writes a new key with string in file, if key exist, value just changes
{
	if (!this->key_exist(key))
	{
		std::string buf = key + '=' + value;
		std::fstream File;
		File.open(this->FILEPATH, std::ios::in | std::ios::out | std::ios::app);
		File << buf << std::endl;
		File.close();
	}
	else
	{
		std::vector <std::string> array;
		std::ifstream file(this->FILEPATH);
		std::string buf;
		while (getline(file, buf))
		{
			if (buf.find(key) != -1) buf = key + '=' + value;
			array.push_back(buf);
		}
		file.close();
		std::ofstream in(this->FILEPATH);
		for (int i = 0; i < array.size(); i++) in << array[i] << std::endl;
		in.close();
	}
}
#pragma once
#include<fstream>
#include <string>
#include <vector>
class Input
{
public:
	Input();
	Input(const std::string& filename);
	void ReadWords(std::vector<std::string>& words);

private:
	std::string m_filename;
};


#include "Input.h"

Input::Input()
{
}

Input::Input(const std::string& filename): m_filename(filename)
{
}

void Input::ReadWords(std::vector<std::string>& words)
{ 
	std::string word;
	for (std::ifstream file(m_filename); !file.eof();/*empty*/)
	{
		file >> word;
		words.emplace_back(word);
	}
}

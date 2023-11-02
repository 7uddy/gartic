#include<iostream>
#include<string>

class Round
{
public:
	Round();
	std::string GetHiddenWord() const;
private:
	uint16_t GenerateHiddenWordIndex() const;
private:
	std::string m_hiddenWord;
	static const uint16_t kWordNumber = 499;
};
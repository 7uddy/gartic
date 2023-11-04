#include<iostream>
#include<string>

class Round
{
public:

	enum class Difficulty : char
	{
		Easy=1, 
		Medium,
		Hard
	};

	Round(Difficulty difficulty);
	std::string GetHiddenWord() const;

private:

	uint16_t GenerateHiddenWordIndex() const;

private:

	std::string m_hiddenWord;
	static const uint16_t kWordNumber = 499;
	Difficulty m_difficulty;
};
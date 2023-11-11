#include<iostream>
#include<string>

class Round
{
public:

	enum class Difficulty : uint8_t
	{
		Easy = 2,
		Medium,
		Hard
	};

	enum class MaxLettersForDifficulty : uint8_t
	{
		Easy = 4,
		Medium = 6,
		Hard = 20
	};

	Round(Difficulty difficulty);
	std::string GetHiddenWord() const;

private:

	uint16_t GenerateHiddenWordIndex() const;
	uint8_t GenerateLettersNumberToShow() const;
	bool VerifyWordDifficultyBalance()const;

private:

	std::string m_hiddenWord;
	static const uint16_t kWordNumber = 499;
	Difficulty m_difficulty;

};
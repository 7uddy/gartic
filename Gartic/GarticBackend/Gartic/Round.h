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
	bool IsHiddenWord(const std::string& word) const;
	void RevealLetter();
private:

	uint16_t GenerateHiddenWordIndex() const;
	uint8_t GenerateLettersNumberToShow();
	bool VerifyWordDifficultyBalance()const;

private:

	std::string m_hiddenWord;
	std::string m_shownWord;
	static const uint16_t kWordNumber = 499;
	Difficulty m_difficulty;
	uint8_t m_lettersToShow;

};
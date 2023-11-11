#include "Round.h"
#include<random>
Round::Round(Difficulty difficulty) :
    m_difficulty{ difficulty }
{
    /*empty*/
}

std::string Round::GetHiddenWord() const
{
    return m_hiddenWord;
}

uint16_t Round::GenerateHiddenWordIndex() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, kWordNumber);
    return distribution(gen);
}

uint8_t Round::GenerateLettersNumberToShow() const
{
    /*
    This function is implemented with the idea that the game will always hint half of the letters, regardless of difficulty.
    */
    uint8_t wordSize = m_hiddenWord.length();
    return wordSize / 2;
}

bool Round::VerifyWordDifficultyBalance() const
{
    /*
    Checks if the hiddenWord is good for the selected difficulty.
    */
    uint8_t wordSize = m_hiddenWord.length();
    if (wordSize > GetMaxLettersForDifficulty(m_difficulty))
    {
        return false;
    }
    else return true;
}

uint8_t DifficultyToInt(Round::Difficulty difficulty)
{
    /*
    Return an int identifier for a given difficulty.
    */
    switch (difficulty)
    {
        using enum Round::Difficulty;
    case Easy:
        return uint8_t(Easy);
    case Medium:
        return uint8_t(Medium);
    case Hard:
        return uint8_t(Hard);
    default:
        return 0;
    }
}

uint8_t GetMaxLettersForDifficulty(Round::Difficulty difficulty)
{
    /*
    Returns how many letters a word can have for a given difficulty.
    */
    switch (difficulty)
    {
    case Round::Difficulty::Easy:
        return static_cast<uint8_t>(Round::MaxLettersForDifficulty::Easy);
    case Round::Difficulty::Medium:
        return static_cast<uint8_t>(Round::MaxLettersForDifficulty::Medium);
    case Round::Difficulty::Hard:
        return static_cast<uint8_t>(Round::MaxLettersForDifficulty::Hard);
    default:
        return 0;
    }
}

std::string_view DifficultyToString(Round::Difficulty difficulty)
{
    switch (difficulty)
    {
        using enum Round::Difficulty;
    case Easy:
        return "Easy";
    case Medium:
        return "Medium";
    case Hard:
        return "Hard";
    default:
        return "";
    }
}
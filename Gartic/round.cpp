#include "Round.h"
#include<random>
Round::Round(Difficulty difficulty) :
    m_difficulty{ difficulty }
{
    m_lettersToShow = 0;
    m_hiddenWord = "";
    m_shownWord = "";
}

std::string Round::GetHiddenWord() const
{
    return m_hiddenWord;
}

bool Round::IsHiddenWord(const std::string& word) const
{
    return word == m_hiddenWord;
}

void Round::RevealLetter()
{
    /*
    TODO: m_shownWord has to be an empty string with size m_hiddenWord for this to work
    */
    uint8_t wordSize = m_hiddenWord.length();
    std::random_device rd;
    std::mt19937 gen(rd());
    while (m_lettersToShow)
    {
        std::uniform_int_distribution<int> distribution(0, wordSize - 1);
        if (m_shownWord[distribution(gen)] == '\0')
        {
            m_shownWord[distribution(gen)] = m_hiddenWord[distribution(gen)];
            m_lettersToShow--;
            break;
        }
    }
}

uint16_t Round::GenerateHiddenWordIndex() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, kWordNumber);
    return distribution(gen);
}

uint8_t Round::GenerateLettersNumberToShow() 
{
    /*
    This function is implemented with the idea that the game will always hint half of the letters, regardless of difficulty.
    */
    uint8_t wordSize = m_hiddenWord.length();
    m_lettersToShow = wordSize / 2;
    return m_lettersToShow;
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
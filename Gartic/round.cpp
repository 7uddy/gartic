#include "Round.h"
#include<random>
Round::Round(Difficulty difficulty):
    m_difficulty{difficulty}
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

uint8_t DifficultyToInt(Round::Difficulty difficulty)
{
    switch (difficulty)
    {
        using enum Round::Difficulty;
    case Easy:
        return 1;
    case Medium:
        return 2;
    case Hard:
        return 3;
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
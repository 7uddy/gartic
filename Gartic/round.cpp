#include "Round.h"
#include<random>
Round::Round()
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

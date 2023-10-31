#include "Game.h"

uint16_t Game::k_numberOfRounds = 4;

uint16_t Game::GetGameID() const
{
    return m_id;
}

std::vector<Player> Game::GetPlayers() const
{
    return m_Players;
}

void Game::SortPlayersByCurrentScore()
{
    std::sort(m_Leaderboard.begin(), m_Leaderboard.end());
}

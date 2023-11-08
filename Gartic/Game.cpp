#include "Game.h"

const uint16_t& Game::GetGameID() const noexcept
{
    return m_gameID;
}

const std::vector<Player>& Game::GetPlayers() const noexcept
{
    return m_Players;
}

void Game::SortPlayersByCurrentScore() noexcept
{
    std::sort(m_Players.begin(), m_Players.end());
}

void Game::AddPlayerToGame(Player&& player)
{
    auto playerFound = std::find(m_Players.begin(), m_Players.end(), player);
    if(playerFound!=m_Players.end())
        throw std::exception("Player with specified ID already exists in current game.");
    m_Players.emplace_back(player);
}

void Game::DeletePlayerFromGameWithID(const uint16_t& ID)
{
    auto playerFound = std::find_if(m_Players.begin(), m_Players.end(),
        [ID](const Player& player) { 
            return player.GetID() == ID;
        });
    if (playerFound == m_Players.end())
        throw std::exception("Player with specified ID does not exist in current game.");
    m_Players.erase(playerFound);
}

#include "Game.h"

Game::Game() : 
    m_roundNumber{ 0 }, m_gameState{ Status::Inactive }, m_gameID{5}
{
    /*EMPTY*/
}

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

void Game::movePlayersHereFromOutside(std::vector<Player>&& playersFromOutside) noexcept
{
    m_Players = std::move(playersFromOutside);
}

std::vector<Player>&& Game::movePlayersFromHere() noexcept
{
    return std::move(m_Players);
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

void Game::ChangeGameStatus() noexcept
{
    //Only changes 
    //Inactive -> Active
    //Active -> Finished
    switch (m_gameState)
    {
    case Status::Inactive:
        m_gameState = Status::Active;
        return;
    case Status::Active:
        m_gameState = Status::Finished;
        return;
    }
}

void Game::startGame() noexcept
{
    //startRound
    choosePainter();
    //getWord
    //getBoard
    //startTimer
}

void Game::choosePainter() noexcept
{
    m_Painter = &m_Players[(m_roundNumber + m_roundNumber / k_numberOfRounds * m_Players.size()) % m_Players.size()];
}

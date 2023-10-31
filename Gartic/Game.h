#pragma once
#include "Player.h"
#include "Input.h"
#include <vector>
#include <algorithm>

class Game
{
public:
	Game();

	uint16_t GetGameID() const;
	std::vector<Player> GetPlayers() const;
	void SortPlayersByCurrentScore();

private:
	std::vector<Round> m_Rounds;
	std::vector<Player> m_Players;
	std::vector<Player> m_Leaderboard;
	uint16_t m_id;

private:
	static uint16_t k_numberOfRounds;
};


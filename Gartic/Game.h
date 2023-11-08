#pragma once
#include "Input.h"
#include "Player.h"
#include "Round.h"

#include <vector>
#include <algorithm>

class Game
{
public:
	/*-------Constructors-------*/
	Game() = default;


	/*-------Game variables related functions-------*/
	const uint16_t& GetGameID() const noexcept;

	const std::vector<Player>& GetPlayers() const noexcept;
	void SortPlayersByCurrentScore() noexcept;

	void AddPlayerToGame(Player&&);
	void DeletePlayerFromGameWithID(const uint16_t&);


private:
	std::vector<Player> m_Players;
	uint16_t m_gameID;

private:
	static const uint16_t k_numberOfRounds = 4;
};


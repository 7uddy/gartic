#pragma once
#include "Input.h"
#include "Player.h"
#include "Round.h"

#include <vector>
#include <algorithm>

class Game
{
public:
	/*-------Enums-------*/
	enum class Status : uint8_t
	{
		Inactive,
		Active,
		Finished
	};


	/*-------Constructors-------*/
	Game();

	void movePlayersHereFromOutside(std::vector<Player>&&);
	std::vector<Player>&& movePlayersFromHere() noexcept;

	/*-------Game variables related functions-------*/
	const uint16_t& GetGameID() const noexcept;


	const std::vector<Player>& GetPlayers() const noexcept;
	void SortPlayersByCurrentScore() noexcept;


	void AddPlayerToGame(Player&&);
	void DeletePlayerFromGameWithID(const uint16_t&);

	void ChangeGameStatus() noexcept;

	void startGame() noexcept;
	void choosePainter() noexcept;

private:
	std::vector<Player> m_Players;
	uint16_t m_gameID;
	Status m_gameState;
	uint32_t m_roundNumber;

private:
	static const uint16_t k_numberOfRounds = 4;
	static Player* m_Painter;
};


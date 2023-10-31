#pragma once
#include "Player.h"
#include "Input.h"
#include <vector>


class Game
{
public:
	Game();
private:
	std::vector<Round> m_Rounds;
	std::vector<Player> m_Players;
	uint16_t m_id;
};


module game;

using namespace gartic;

void Game::startAnotherRound() noexcept
{
	m_round.startRound();
}

void gartic::Game::showAllPlayers() const noexcept
{
	for (auto& player : m_players)
		std::cout << player.getUsername() << " ";
}

uint16_t gartic::Game::getTimer() const noexcept
{
	return m_round.getSecondsFromStart();
}

const std::vector<Player>& gartic::Game::getPlayers() const noexcept
{
	return m_players;
}

const uint16_t& gartic::Game::getGameID() const noexcept
{
	return m_gameID;
}

void Game::setPlayers(std::vector<Player>&& players) noexcept
{
	m_players = std::move(players);
}

void Game::addPlayerToGame(Player&& newPlayer)
{
	m_players.emplace_back(std::move(newPlayer));
}

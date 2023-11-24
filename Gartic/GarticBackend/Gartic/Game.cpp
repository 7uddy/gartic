import game;

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

void Game::setPlayers(std::vector<Player>&& players) noexcept
{
	m_players = std::move(players);
}
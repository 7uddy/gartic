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

void gartic::Game::AddMessageToChat(const std::string& message) noexcept
{
	m_chat.emplace_back(message);
}

void gartic::Game::ClearChat() noexcept
{
	m_chat.clear();
}

std::string gartic::Game::GetChat() const noexcept
{
	std::string chat{};
	for (auto& message : m_chat)
		chat += message + '\n';
	return chat;
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

void gartic::Game::deletePlayerFromGameWithID(const uint16_t& id)
{
	for (auto it = m_players.begin(); it != m_players.end(); ++it)
		if (it->getID() == id)
		{
			m_players.erase(it);
			return;
		}
	throw std::exception("DELETE ERROR: ID NOT FOUND");
}

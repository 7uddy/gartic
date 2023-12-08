module game;

using namespace gartic;


void gartic::Game::changeDifficulty(int difficultyIndex) noexcept
{
	m_round.SetDifficulty(difficultyIndex);
}

uint16_t gartic::Game::GetDifficulty() const noexcept
{
	return m_round.GetDifficulty();
}

void Game::startAnotherRound() noexcept
{
	m_round.startRound();
}

void gartic::Game::showAllPlayers() const noexcept
{
	for (auto& player : m_players)
		std::cout << player.GetUsername() << " ";
}

bool gartic::Game::IsPlayerInGame(const Player& newPlayer) const noexcept
{
	for (const auto& player : m_players)
	{
		if (player.GetID() == newPlayer.GetID())
			return true;
	}
	return false;
}

uint16_t gartic::Game::getTimer() const noexcept
{
	return m_round.getSecondsFromStart();
}

const std::vector<Player>& gartic::Game::getPlayers() const noexcept
{
	return m_players;
}

void gartic::Game::AddMessageToChat(const uint16_t& id, const std::string& message) noexcept
{
	if (id == 0)
	{
		m_chat.emplace_back(std::make_pair(std::optional<uint16_t>(), message));
	}
	else
	{
		m_chat.emplace_back(std::make_pair(std::optional<uint16_t>(id), message));
	}
}

void gartic::Game::ClearChat() noexcept
{
	m_chat.clear();
}

std::string gartic::Game::GetChat(const uint16_t& id) const noexcept
{
	std::string chat{};
	for (auto& message : m_chat)
	{
		if (!message.first.has_value())
		{
			chat += message.second + '\n';
			continue;
		}
		if(message.first.value()==id)
			chat += message.second + '\n';
	}
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
		if (it->GetID() == id)
		{
			m_players.erase(it);
			return;
		}
	throw std::exception("DELETE ERROR: ID NOT FOUND");
}

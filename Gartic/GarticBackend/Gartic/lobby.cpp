module lobby;

using namespace gartic;

gartic::Lobby::Lobby() : m_lobbyStatus{Status::WaitingForPlayers}, m_lobbyCode{}
{
	GenerateLobbyCode();
}

void Lobby::addPlayer(Player&& player) noexcept
{
	m_players.emplace_back(std::move(player));
}

void Lobby::removePlayer(const std::string& username)
{
	for (auto it = m_players.begin(); it!=m_players.end();++it)
		if (it->getUsername() == username)
		{
			m_players.erase(it);
			return;
		}
	throw std::exception("DELETE ERROR: USERNAME NOT FOUND");
}

void Lobby::clearLobby() noexcept
{
	m_players.clear();
	m_lobbyStatus = Status::Terminated;
}

uint16_t Lobby::getNumberOfPlayers() const noexcept
{
	return static_cast<uint16_t>(m_players.size());
}

const std::string& Lobby::getLobbyCode() const noexcept
{
	return m_lobbyCode;
}

const Lobby::Status& gartic::Lobby::getStatusOfLobby() const noexcept
{
	return m_lobbyStatus;
}

void gartic::Lobby::StartGame(gartic::Game& game)
{
	game.setPlayers(std::move(m_players));
	m_lobbyStatus = Status::Launched;
}

bool gartic::Lobby::CheckLobbyCode(const std::string& code) const
{
	return m_lobbyCode == code;
}

void gartic::Lobby::GenerateLobbyCode()
{
	for (int i = 0; i < k_lengthOfLobbyCode; i++)
	{
		m_lobbyCode.push_back(static_cast<char>(GetRandomDigit()));
	}
}

int gartic::Lobby::GetRandomDigit(int maxim) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(48, maxim);
	return distrib(gen);
}

bool Lobby::isInLobby(const std::string& username) const
{
	for (auto& player : m_players)
		if (player.getUsername() == username) return true;
	return false;
}

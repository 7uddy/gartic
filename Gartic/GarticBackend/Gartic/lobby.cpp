import lobby;

using namespace gartic;

gartic::Lobby::Lobby() : m_lobbyCode{ "1234" }, m_lobbyStatus{Status::WaitingForPlayers}
{
	/*EMPTY*/
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

std::vector<Player> Lobby::getPlayersToMove()
{
	return std::move(m_players);
}

const Lobby::Status& gartic::Lobby::getStatusOfLobby() const noexcept
{
	return m_lobbyStatus;
}

bool Lobby::isInLobby(const std::string& username) const
{
	for (auto& player : m_players)
		if (player.getUsername() == username) return true;
	return false;
}

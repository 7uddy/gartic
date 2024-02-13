module lobby;

using namespace gartic;

Lobby::Lobby() : m_lobbyStatus{ Status::WaitingForPlayers }, m_requestsToDeleteLobby{ 0 }, m_numberOfPlayers{ 0 }
{
	GenerateLobbyCode();
}

void Lobby::AddRequestForEnd() noexcept
{
	++m_requestsToDeleteLobby;
}

bool Lobby::TimeToDeleteLobby() const noexcept
{
	return (m_requestsToDeleteLobby == m_numberOfPlayers);
}

void Lobby::AddPlayer(std::unique_ptr<Player>& player)
{
	if(IsInLobby(player.get()->GetUsername()))
		throw std::exception("ADD ERROR: PLAYER ALREADY IN LOBBY");
	m_players.emplace(std::make_pair(player.get()->GetUsername(), std::move(player)));
	++m_numberOfPlayers;
}

void Lobby::RemovePlayer(const std::string& username)
{
	if (!IsInLobby(username))
		throw std::exception("REMOVE ERROR: PLAYER NOT FOUND IN LOBBY");
	m_players.erase(username);
	--m_numberOfPlayers;
}

void Lobby::ClearLobby() noexcept
{
	m_players.clear();
	m_lobbyStatus = Status::Launched;
}

uint16_t Lobby::GetNumberOfPlayers() const noexcept
{
	return static_cast<uint16_t>(m_players.size());
}

std::vector<std::string> Lobby::GetUsernamesOfPlayers() const noexcept
{
	std::vector<std::string> usernames;
	for (const auto& player : m_players)
	{
		usernames.emplace_back(player.first);
	}
	return usernames;
}

const std::string& Lobby::GetLobbyCode() const noexcept
{
	return m_lobbyCode;
}

int Lobby::GetStatusOfLobby() const noexcept
{
	return ConvertStatusToInteger(m_lobbyStatus);
}

bool Lobby::CheckLobbyCode(const std::string& code) const
{
	return m_lobbyCode == code;
}

void Lobby::MovePlayersToGame(Game& game)
{
	for (auto& player : m_players)
	{
		game.AddPlayerToGame(std::move(player.second));
	}
	ClearLobby();
}

void Lobby::GenerateLobbyCode() noexcept
{
	std::pair<int, int> ASCIIValueOfAAndZ{ 65,90 };
	std::pair<int, int> ASCIIValueOfaAndz{ 97,122 };
	std::pair<int, int> ASCIIValueOf0And9{ 48,57 };

	int choice{};
	do
	{
		choice = GetRandomDigit({ 0,2 });
		switch (choice)
		{
			case 0:
			{
				m_lobbyCode.push_back(static_cast<char>(GetRandomDigit(ASCIIValueOfAAndZ)));
				break;
			}
			case 1:
			{
				m_lobbyCode.push_back(static_cast<char>(GetRandomDigit(ASCIIValueOfaAndz)));
				break;
			}
			case 2:
			{
				m_lobbyCode.push_back(static_cast<char>(GetRandomDigit(ASCIIValueOf0And9)));
				break;
			}
			default:
			{
				/*EMPTY*/
			}
		}
	} while (m_lobbyCode.size() != k_lengthOfLobbyCode);
}

int Lobby::GetRandomDigit(const std::pair<int, int>& values) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(values.first, values.second);
	return distrib(gen);
}

int Lobby::ConvertStatusToInteger(const Status& current) const noexcept
{
	switch (current)
	{
		case (Status::WaitingForPlayers):
			return 0;
		case (Status::Launched):
			return 1;
		default:
			return -1;
	}
}

bool Lobby::IsInLobby(const std::string& username) const
{
	return m_players.contains(username);
}

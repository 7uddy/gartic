module game;
import word;

using namespace gartic;

const int& Game::GetGameID() const noexcept
{
	return m_gameID;
}

Game::Game(int gameID) : m_gameID{ gameID }, m_gameState{ Status::Inactive }
{
	/*EMPTY*/
}

void Game::SetStatusOfGame(const Status& newStatus)
{
	m_gameState = newStatus;
}

void Game::StartAnotherRound(GarticDatabase& storage) noexcept
{
	if (m_gameState == Status::Finished || m_gameState == Status::Inactive)
		return;
	do {
		Word word = storage.GetRandomWordWithDifficulty(GetDifficulty());
		if (std::find(pastWords.begin(), pastWords.end(), word) == pastWords.end())
		{
			pastWords.emplace_back(word); std::cout << "HERE\n";
			if (!m_round.StartRound(word))
			{
				std::cout << "HERE";
				m_gameState = Status::Finished;
				for (const auto& player : m_players)
				{
					//void AddScoreToDatabase(int gameID, std::string username, float score);
					storage.AddScoreToDatabase(m_gameID, player.first, player.second->GetScore());
				}
			}
			break;
		}
	} while (true);
}

void Game::AddPlayerToGame(std::unique_ptr<Player> player)
{
	std::shared_ptr<Player> newPlayer{ std::move(player) };
	m_players.emplace(std::make_pair(newPlayer->GetUsername(), newPlayer));
	m_round.AddPlayer(newPlayer);
}

void Game::UpdateBoard(const std::array<uint16_t, kSize>& newBoard)
{
	m_board = newBoard;
}

bool Game::IsPlayerInGame(std::string_view username) const noexcept
{
	return m_players.contains(std::string(username));
}

uint16_t Game::GetTimer() const noexcept
{
	return m_round.GetSecondsFromStart();
}

void Game::AddMessageToChat(const std::string& message, const std::string& username) noexcept
{
	//IN CASE THE MESSAGE IS FROM SYSTEM
	/*if (username.empty())
	{
		std::string messageToBeAdded{ "[SYSTEM]: " + message };
		m_chat.emplace_back(std::make_pair(std::optional<std::string>(), std::move(messageToBeAdded));
		return;
	}*/

	//FORMAT NEW MESSAGE
	std::string messageToBeAdded{ "[" + username + "]: " + message };

	//CHECK IF MESSAGE HAS A SPACE IN IT => IT IS NOT A GUESS
	if (message.find(' ') != message.npos)
	{
		//ADD MESSAGE FOR EVERYONE SINCE IT IS NOT A GUESS
		m_chat.emplace_back(std::make_pair(std::optional<std::string>(), std::move(messageToBeAdded)));
		return;
	}

	//MESSAGE DOES NOT HAVE A SPACE => IT IS A GUESS

	//CHECK IF THE MESSAGE IS THE HIDDEN WORD
	if (!m_round.IsHiddenWord(message))
	{
		//ADD MESSAGE FOR EVERYONE SINCE IT WAS NOT CORRECT
		m_chat.emplace_back(std::make_pair(std::optional<std::string>(), std::move(messageToBeAdded)));
		return;
	}
	//IF HERE => MESSAGE IS HIDDEN WORD => ADD GUESS TIME FOR PLAYER
	m_round.AddPlayerGuessTime(username);
	//ADD MESSAGE ONLY FOR PLAYER
	m_chat.emplace_back(std::make_pair(std::optional<std::string>(username), std::move(messageToBeAdded)));
	//ADD MESSAGE OF CONGRATULATIONS ONLY TO PLAYER
	m_chat.emplace_back(std::make_pair(std::optional<std::string>(username), std::string{ "[SYSTEM]: FELICITARI! AI GHICIT CUVANTUL" }));

}

void Game::ClearChat() noexcept
{
	m_chat.clear();
}

std::vector<std::string> Game::GetChat(std::string_view user) const noexcept
{
	std::vector<std::string> chat;
	std::string username(user);
	for (const auto& message : m_chat)
	{
		if (!message.first.has_value())
			chat.emplace_back(message.second);
		else
		{
			if (message.first.value() == username)
				chat.emplace_back(message.second);
		}
	}
	return chat;
}

const std::string& gartic::Game::GetPainterUsername() const noexcept
{
	return m_round.GetPainterUsername();
}

const std::string& gartic::Game::GetHiddenWord() const noexcept
{
	return m_round.GetHiddenWord();
}

const std::string& gartic::Game::GetShownWord() const noexcept
{
	return m_round.GetShownWord();
}

void Game::RemovePlayer(std::string_view username)
{
	if (std::string usernameString(username); !m_players.contains(usernameString))
		throw std::exception("UNABLE TO DELETE PLAYER FROM GAME: DOESN'T EXIST");
	else
		m_players.erase(usernameString);
}

void Game::ChangeDifficulty(int difficulty) noexcept
{
	try
	{
		m_round.SetDifficulty(difficulty);
	}
	catch (...)
	{
		throw std::exception("INVALID DIFFICULTY");
	}
}

void gartic::Game::IsTimeForHint()
{
	uint16_t seconds = GetTimer();
	float multiple = (float)seconds / m_round.GetTimeForHint();
	if (multiple == (int)multiple && !m_round.WasHintShown(multiple - 1))
	{
		m_round.GetNextHint();
	}
}

uint16_t Game::GetDifficulty() const noexcept
{
	return m_round.GetDifficulty();
}

uint16_t Game::GetRoundNumber() const noexcept
{
	return m_round.GetCurrentRound();
}

std::vector<std::shared_ptr<Player>> Game::GetPlayers() const noexcept
{
	/*std::vector<std::shared_ptr<Player>> players;
	for (const auto& play : m_players)
		players.push_back(play.second);
	return players;*/
	return m_round.GetPlayers();
}

void Game::ShowAllPlayers() const noexcept
{
	for (const auto& player : m_players)
	{
		std::cout << player.first << "\n";
	}
}

std::array<uint16_t, Game::kSize> Game::GetBoard() const noexcept
{
	return m_board;
}

int Game::ConvertStatusToInteger(const Game::Status& current) const noexcept
{
	switch (current)
	{
	case (Status::Inactive):
		return 0;
	case (Status::Active):
		return 1;
	case (Status::Finished):
		return 2;
	default:
		return -1;
	}
}

const int& Game::GetGameStatus() const noexcept
{
	return ConvertStatusToInteger(m_gameState);
}
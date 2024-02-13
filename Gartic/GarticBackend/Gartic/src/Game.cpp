module game;
import word;

using namespace gartic;

const int& Game::GetGameID() const noexcept
{
	return m_gameID;
}

Game::Game(int gameID) : m_gameID{ gameID }, m_gameState{ Status::Inactive }, m_requestsToEndGame{0}
{
	/*EMPTY*/
}

void Game::SetStatusOfGame(const Status& newStatus)
{
	m_gameState = newStatus;
}

void Game::StartAnotherRound(GarticDatabase& storage) noexcept
{
	if (m_gameState == Status::Finished || m_gameState == Status::Transitioning)
		return;
	m_gameState = Status::Transitioning;
	do {
		Word word = storage.GetRandomWordWithDifficulty(GetDifficulty());
		if (std::find(pastWords.begin(), pastWords.end(), word) == pastWords.end())
		{
			pastWords.emplace_back(word);
			if (!m_round.StartRound(word))
			{
				m_gameState = Status::Finished;
				return;
			}
			m_board.clear();
			break;
		}
	} while (true);
	m_gameState = Status::Active;
}

void Game::AddPlayerToGame(std::unique_ptr<Player> player)
{
	std::shared_ptr<Player> newPlayer{ std::move(player) };
	m_players.emplace(std::make_pair(newPlayer->GetUsername(), newPlayer));
	m_round.AddPlayer(newPlayer);
}

bool Game::IsPlayerInGame(std::string_view username) const noexcept
{
	return m_players.contains(std::string(username));
}

uint16_t Game::GetTimer() const noexcept
{
	return m_round.GetSecondsFromStart();
}

bool Game::AddMessageToChat(std::string&& message, const std::string& username) noexcept
{
	//FORMAT NEW MESSAGE
	std::string messageToBeAdded{ "[" + username + "]: " + message };

	//CHECK IF RECEIVED MESSAGE HAS A SPACE IN IT => IT IS NOT A GUESS
	if (message.find(' ') != message.npos)
	{
		//ADD MESSAGE FOR EVERYONE SINCE IT IS NOT A GUESS
		m_chat.emplace_back(std::make_pair(std::optional<std::string>(), std::move(messageToBeAdded)));
		return false;
	}

	//MESSAGE DOES NOT HAVE A SPACE => IT IS A GUESS

	//CHECK IF THE MESSAGE IS THE HIDDEN WORD
	if (!m_round.IsHiddenWord(message))
	{
		//ADD MESSAGE FOR EVERYONE SINCE IT WAS NOT CORRECT
		m_chat.emplace_back(std::make_pair(std::optional<std::string>(), std::move(messageToBeAdded)));
		return false;
	}
	//IF HERE => MESSAGE IS HIDDEN WORD => ADD GUESS TIME FOR PLAYER
	m_round.AddPlayerGuessTime(username);
	//ADD THIS MESSAGE ONLY FOR PLAYER
	m_chat.emplace_back(std::make_pair(std::optional<std::string>(username), std::move(messageToBeAdded)));
	//ADD MESSAGE OF ACKNOWLEDGEMENT OF PLAYER'S GUESSING FOR EVERYONE
	m_chat.emplace_back(std::make_pair(std::optional<std::string>(), std::string{ "[SYSTEM]: " + username +" A GHICIT CUVANTUL" }));
	return true;
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

void Game::ChangeDifficulty(int difficulty)
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
	int multiple = (int)seconds / m_round.GetTimeForHint();
	if (!m_round.WasHintShown(multiple - 1))
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

std::vector<std::shared_ptr<Player>> Game::GetPlayers() noexcept
{
	return m_round.GetPlayers();
}

const std::vector<Game::Coordinate>& Game::GetBoard() const noexcept
{
	return m_board;
}

void Game::UpdateBoard(std::vector<Game::Coordinate>&& newBoard)
{
	m_board = std::move(newBoard);
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
	case(Status::Transitioning):
		return 3;
	default:
		return -1;
	}
}

const int& Game::GetGameStatus() const noexcept
{
	return ConvertStatusToInteger(m_gameState);
}

bool Game::AllPlayersGuessed() const noexcept
{
	return m_round.AllGuessersHaveAnswered();
}

void Game::AddRequestForEnd() noexcept
{
	++m_requestsToEndGame;
}

bool Game::TimeToEndGame() const noexcept
{
	return (m_requestsToEndGame == m_players.size());
}

void Game::SaveScoresInDatabase(GarticDatabase& storage) const noexcept
{
	auto saveScoresInDatabase = [this, &storage](const std::pair<std::string, std::shared_ptr<Player>>& player) {
		storage.AddScoreToDatabase(m_gameID, player.first, player.second->GetScore());
		};
	std::ranges::for_each(m_players, saveScoresInDatabase);
}
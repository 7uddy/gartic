module game;

using namespace gartic;

const std::string& Game::GetGameID() const noexcept
{
	return m_gameID;
}

void Game::StartAnotherRound() noexcept
{
	m_round.StartRound();
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

void Game::AddMessageToChat(std::string_view username, std::string_view message) noexcept
{
	//TO BE REWORKED
	// 
	// 
	//CHECK IF MESSAGE HAS A SPACE IN IT => IT IS A GUESS
	if (message.find(' ') == message.npos)
	{
		//CHECK IF THE MESSAGE IS THE HIDDEN WORD
		//if(IsHiddenWord(message))
		// {
		//		m_chat.emplace_back(std::make_pair(std::optional<std::string>(username), message));
		//		m_chat.emplace_back(std::make_pair(std::optional<std::string>(username), std::string{"FELICITARI! AI GHICIT CUVANTUL}));
		// }
		// //ADD MESSAGE FOR EVERYONE SINCE IT WAS NOT CORRECT
		//else
		// {
		//		m_chat.emplace_back(std::make_pair(std::optional<std::string>(), message));
		// }
	}
	//ADD MESSAGE FOR EVERYONE SINCE IT IS NOT A GUESS
	else
	{
		m_chat.emplace_back(std::make_pair(std::optional<std::string>(), std::string{ message }));
	}
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
			chat.emplace_back("SYSTEM: " + message.second);
		else
		{
			if (message.first.value() == username)
				chat.emplace_back(message.first.value() + ": " + message.second);
		}
	}
	return chat;
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
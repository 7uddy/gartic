module round;
using namespace gartic;

std::shared_ptr<Player> Round::m_painter{nullptr};

void Round::StartRound(const Word& word)
{
	static const int numberOfDifficulties = 2;
	ChoosePainter();
	if (m_miniRoundNumber > m_players.size() * k_numberOfRounds)
		throw std::exception("NUMBER OF ROUND IS BIGGER THAN POSSIBLE");
	++m_miniRoundNumber;
	//Template to changing difficulty between rounds
	/*if (m_miniRoundNumber - 1 != 0)
	{
		if (!m_difficultyIsAscending)
			;
		else
			if (m_miniRoundNumber / k_numberOfRounds != (m_miniRoundNumber - 1) / k_numberOfRounds)
			{
				auto difficultyAsInt = GetDifficulty();
				if (difficultyAsInt + 1 <= numberOfDifficulties)
					SetDifficulty(difficultyAsInt + 1);
			}
	}*/
	////std::string word{ GetHiddenWord() };
	m_startRoundTime = std::chrono::steady_clock::now();
	if (word.GetDifficulty() == DifficultyToInteger(m_difficulty))
	{
		m_hiddenWord = word.GetWord();
		m_lettersToShow = m_hiddenWord.size() / 2;
	}
	else
		throw std::exception("Word difficulty doesn't match with round difficulty");
}

void Round::ChoosePainter() noexcept
{
	int index_of_new_painter = (m_miniRoundNumber + m_miniRoundNumber / k_numberOfRounds * static_cast<int>(m_players.size())) % static_cast<int>(m_players.size());
	m_painter = m_players[index_of_new_painter];
}

void Round::CalculateScoreForPlayers() noexcept
{
	for (auto& player : m_players)
	{
		UpdateScoreForPlayer(player);
	}
	m_guessTimes.clear();
}

void Round::AddPlayerGuessTime(const std::string& username)
{
	uint16_t seconds{ GetSecondsFromStart() };
	auto result = std::find_if(m_players.begin(), m_players.end(), [username](const std::shared_ptr<Player>& player) {
		return player.get()->GetUsername() == username; });
	if (result == m_players.end()) 
		throw std::exception("PLAYER NOT FOUND");
	m_guessTimes.insert({result->get()->GetUsername(), seconds});
}

void Round::UpdateScoreForPlayer(std::shared_ptr<Player> player) noexcept
{
	if (player == m_painter)
	{
		if (m_guessTimes.empty())
			player->AddToScore(-100);
		else
		{
			float average {0};
			for (const auto& pairOfUsernameAndGuessTime : m_guessTimes)
			{
				average += pairOfUsernameAndGuessTime.second;
			}
			average /= m_guessTimes.size();
			auto score = (60 - average) * 100 / 60;
			player->AddToScore(score);
		}
		return;
	}
	float seconds = m_guessTimes.at(player.get()->GetUsername());
	if (seconds == 60)
	{
		player->AddToScore(-50);
		return;
	}
	if (seconds < 30)
	{
		player->AddToScore(100);
		return;
	}
	auto score = (60 - seconds) * 100 / 30;
	player->AddToScore(score);
}

uint16_t Round::DifficultyToInteger(const Difficulty& difficulty) const
{
	switch (difficulty)
	{
	case Difficulty::Easy:
		return 0u;
	case Difficulty::Medium:
		return 1u;
	case Difficulty::Hard:
		return 2u;
	default:
		throw std::exception("UNABLE TO CONVERT DIFFICULTY TO INT");
	}
}

Round::Difficulty Round::IntegerToDifficulty(int difficulty) const
{
	auto resultAsUInt = static_cast<uint8_t>(difficulty);
	switch (resultAsUInt)
	{
	case 0u:
		return Difficulty::Easy;
	case 1u:
		return Difficulty::Medium;
	case 2u:
		return Difficulty::Hard;
	}
	throw std::exception("UNABLE TO CONVERT INT TO DIFFICULTY");
}

void Round::EndRound() noexcept
{
	CalculateScoreForPlayers();
}

uint16_t Round::GetCurrentRound() const noexcept
{
	return m_miniRoundNumber / k_numberOfRounds + 1;
}

uint16_t Round::GetSecondsFromStart() const noexcept
{
	const Time timeNow = std::chrono::steady_clock::now();
	auto integer = std::chrono::duration_cast<std::chrono::seconds>(timeNow - m_startRoundTime);
	return static_cast<uint16_t>(integer.count());

}

void Round::SetDifficulty(int difficultyAsInt)
{
	if (difficultyAsInt < 0 || difficultyAsInt>3)
		throw std::exception("UNABLE TO SET DIFFICULTY: INVALID DATA");
	switch (difficultyAsInt)
	{
	case 3:
		m_difficultyIsAscending = true;
		m_difficulty = Difficulty::Easy;
		break;
	default:
		m_difficultyIsAscending = false;
		m_difficulty = IntegerToDifficulty(difficultyAsInt);
	}
}

uint16_t Round::GetDifficulty() const noexcept
{
	return DifficultyToInteger(m_difficulty);
}

const std::string& Round::GetPainterUsername() const noexcept
{
	return m_painter->GetUsername();
}

const std::string& gartic::Round::GetHiddenWord() const noexcept
{
	return m_hiddenWord;
}

const std::string& gartic::Round::GetShownWord() const noexcept
{
	return m_shownWord;
}

bool gartic::Round::IsHiddenWord(const std::string& receivedWord)
{
	return receivedWord == m_hiddenWord;
}

const std::vector<std::shared_ptr<Player>> Round::GetPlayers() const noexcept
{
	if (m_players.at(0) != m_painter)
	{
		//to be done
		std::cout << "FIRST PLAYER IS NOT PAINTER";
		/*auto painter = std::find(m_players.begin(), m_players.end(), m_painter);
		std::swap(painter, m_players[0]);*/
	}
	return m_players;
}

void Round::ShowAllPlayers() const noexcept
{
	for (const auto& player: m_players)
	{
		std::cout << player.get()->GetUsername() << " ";
	}
}

void Round::ShowAllPlayerGuessTimes() const noexcept
{
	for (const auto& pair : m_guessTimes)
	{
		std::cout << pair.first << " " << pair.second << "\n";
	}
}

void Round::AddPlayer(std::shared_ptr<Player> player)
{
	m_players.emplace_back(player);
}

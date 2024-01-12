module round;
using namespace gartic;

std::shared_ptr<Player> Round::m_painter{ nullptr };

bool Round::StartRound(const Word& word)
{
	if(m_miniRoundNumber != 0)
		CalculateScoreForPlayers();
	static const int numberOfDifficulties = 2;
	if (m_miniRoundNumber + 1 > m_players.size() * k_numberOfRounds)
		return false;
	ChoosePainter();
	++m_miniRoundNumber;
	//Template to changing difficulty between rounds
	////std::string word{ GetHiddenWord() };
	if (word.GetDifficulty() == DifficultyToInteger(m_difficulty))
	{
		m_hiddenWord = word.GetWord();
		std::fill(m_lettersToShow.begin(), m_lettersToShow.end(), false);
		//m_lettersToShow.clear();
		m_lettersToShow.resize(m_hiddenWord.size() / 2, false);
		m_timeForHint = (k_roundSeconds - 10) / m_lettersToShow.size();
		m_shownWord.assign(m_hiddenWord.size(), '_');
	}
	else
		throw std::exception("Word difficulty doesn't match with round difficulty");

	if(m_difficultyIsAscending)
	{
		//if in first mini_round
		/*if (m_miniRoundNumber - 1 == 0)
			continue;*/
		//If another bigRound has started
		if (m_miniRoundNumber / k_numberOfRounds != (m_miniRoundNumber - 1) / k_numberOfRounds)
		{
			auto difficultyAsInt = GetDifficulty();
			if (difficultyAsInt + 1 <= numberOfDifficulties)
				SetDifficulty(difficultyAsInt + 1);
		}
	}
	m_startRoundTime = std::chrono::steady_clock::now();
	return true;
}

void Round::ChoosePainter() noexcept
{
	//int index_of_new_painter = (m_miniRoundNumber + m_miniRoundNumber / k_numberOfRounds * static_cast<int>(m_players.size())) % static_cast<int>(m_players.size());
	int index_of_new_painter = m_miniRoundNumber % static_cast<int>(m_players.size());
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
	/*auto result = std::find_if(m_players.begin(), m_players.end(), [username](const std::shared_ptr<Player>& player) {
		return player.get()->GetUsername() == username; });
	if (result == m_players.end())
		throw std::exception("PLAYER NOT FOUND");*/
	m_guessTimes.insert({ username, seconds });
}

void Round::UpdateScoreForPlayer(std::shared_ptr<Player> player) noexcept
{
	if (player == m_painter)
	{
		if (m_guessTimes.empty())
			player->AddToScore(-100);
		else
		{
			float average{ 0 };
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
	float seconds{};
	if (m_guessTimes.contains(player.get()->GetUsername()))
		seconds = m_guessTimes.at(player.get()->GetUsername());
	else
		seconds = 60;
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

void gartic::Round::GetNextHint() noexcept
{
	int index = GetRandomIndex();
	m_shownWord[index] = m_hiddenWord[index];
	auto position = std::find(m_lettersToShow.begin(), m_lettersToShow.end(), false);
	if (position != m_lettersToShow.end())
	{
		auto pos = std::distance(m_lettersToShow.begin(), position);
		m_lettersToShow[pos] = true;
	}
}

int gartic::Round::GetRandomIndex() const noexcept
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int randomIndex;
	int counter = 0;
	do
	{
		std::uniform_int_distribution<> distrib(0, m_hiddenWord.size() - 1);
		randomIndex = distrib(gen);
		/*if (++counter == m_hiddenWord.size())
		{
			throw std::exception("Shown word has no empty space to add hint.");
		}*/
	} while (m_shownWord[randomIndex] != '_');
	return randomIndex;
}

void Round::EndRound() noexcept
{
	CalculateScoreForPlayers();
}

uint16_t Round::GetCurrentRound() const noexcept
{
	return ((m_miniRoundNumber - 1) / m_players.size()) + 1;
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

const int gartic::Round::GetTimeForHint() const noexcept
{
	return m_timeForHint;
}

const int gartic::Round::GetNumberOfHints() const noexcept
{
	return m_lettersToShow.size();
}

const bool gartic::Round::WasHintShown(const int& index) const noexcept
{
	if (index < m_lettersToShow.size())
	{
		return (m_lettersToShow[index] == true);
	}
	//Returns true if vector subscripts out of range for if statement from game.IsTimeForHint()
	return true;
}

bool gartic::Round::IsHiddenWord(const std::string& receivedWord)
{
	return receivedWord == m_hiddenWord;
}

std::vector<std::shared_ptr<Player>> Round::GetPlayers() noexcept
{
	std::vector<std::shared_ptr<Player>> result;
	result.emplace_back(m_painter);
	for (const auto& player : m_players)
		if (player != m_painter)
			result.emplace_back(player);
	//std::vector<std::shared_ptr<Player>> result{ m_players };
	//if (result.at(0) != m_painter)
	//{
	//	//to be done
	//	std::cout << "FIRST PLAYER IS NOT PAINTER";
	//	for(size_t index=1;index< result.size();index++)
	//		if (result[index] == m_painter)
	//		{
	//			std::swap(result[index], result[0]);
	//			/*std::shared_ptr<Player> copy = m_players[0];
	//			m_players[0] = m_players[index];
	//			m_players.at(index) = copy;
	//			copy.reset();*/
	//			break;
	//		}
	//	/*auto painter = std::find(m_players.begin(), m_players.end(), m_painter);
	//	std::swap(painter, m_players[0]);*/
	//}
	return result;
}

void Round::ShowAllPlayers() const noexcept
{
	for (const auto& player : m_players)
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

bool Round::AllGuessersHaveAnswered() const noexcept
{
	return ((m_guessTimes.size() - 1) == m_players.size());
}
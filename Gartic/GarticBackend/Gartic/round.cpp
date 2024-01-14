module round;
using namespace gartic;

std::shared_ptr<Player> Round::m_painter{ nullptr };

bool Round::StartRound(const Word& word)
{
	static const int numberOfDifficulties = 2;
	//IF DIFFERENT FROM FIRST MINIROUND
	if(m_miniRoundNumber != 0)
		CalculateScoreForPlayers();
	//CHECK IF I CAN START NEXT ROUND
	if (m_miniRoundNumber + 1 > m_players.size() * kNumberOfRounds)
		return false;
	ChoosePainter();
	++m_miniRoundNumber;
	if (word.GetDifficulty() == DifficultyToInteger(m_difficulty))
	{
		m_hiddenWord = word.GetWord();
		std::fill(m_lettersToShow.begin(), m_lettersToShow.end(), false);
		//m_lettersToShow.clear();
		m_lettersToShow.resize(m_hiddenWord.size() / 2, false);
		m_timeForHint = (kRoundSeconds - 10) / m_lettersToShow.size();
		m_shownWord.assign(m_hiddenWord.size(), '_');
	}

	//Template to changing difficulty between rounds
	if(m_difficultyIsAscending)
	{
		//CHECK IF NEXT_BIG_ROUND STARTS NEXT ROUND
		if (((m_miniRoundNumber - 1) / m_players.size()) != (m_miniRoundNumber / m_players.size()))
		{
			auto difficultyAsInt{ GetDifficulty() };
			SetDifficulty((difficultyAsInt + 1) % numberOfDifficulties);
		}
	}
	m_startRoundTime = std::chrono::steady_clock::now();
	return true;
}

void Round::ChoosePainter() noexcept
{
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
	m_guessTimes.insert({ username, seconds });
}

void Round::UpdateScoreForPlayer(std::shared_ptr<Player> player) noexcept
{
	//CALCULATE SCORE FOR PAINTER
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
	//CALCULATE SCORE FOR GUESSERS
	float seconds{};
	//IF PLAYER HAS GUESSED
	if (m_guessTimes.contains(player.get()->GetUsername()))
		seconds = m_guessTimes.at(player.get()->GetUsername());
	//ELSE HE HAS NOT GUESSED
	else
		seconds = kRoundSeconds;
	if (seconds == kRoundSeconds)
	{
		player->AddToScore(-50);
		return;
	}
	if (seconds < 30)
	{
		player->AddToScore(100);
		return;
	}
	auto score = (kRoundSeconds - seconds) * 100 / 30;
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
	int index{ GetRandomIndex() };
	m_shownWord[index] = m_hiddenWord[index];
	if (auto position = std::ranges::find(m_lettersToShow, false); position != m_lettersToShow.end())
	{
		auto pos{ std::distance(m_lettersToShow.begin(), position) };
		m_lettersToShow[pos] = true;
	}
}

int gartic::Round::GetRandomIndex() const noexcept
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int randomIndex{};
	do
	{
		std::uniform_int_distribution<> distrib(0, m_hiddenWord.size() - 1);
		randomIndex = distrib(gen);
	} while (m_shownWord[randomIndex] != '_');

	return randomIndex;
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
		//m_difficultyIsAscending = false;
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

const std::string& Round::GetHiddenWord() const noexcept
{
	return m_hiddenWord;
}

const std::string& Round::GetShownWord() const noexcept
{
	return m_shownWord;
}

int Round::GetTimeForHint() const noexcept
{
	return m_timeForHint;
}

int Round::GetNumberOfHints() const noexcept
{
	return m_lettersToShow.size();
}

bool Round::WasHintShown(const int& index) const noexcept
{
	if (index < m_lettersToShow.size())
	{
		return (m_lettersToShow[index] == true);
	}
	//Returns true if vector subscripts out of range for if statement from game.IsTimeForHint()
	return true;
}

bool Round::IsHiddenWord(const std::string& receivedWord)
{
	return receivedWord == m_hiddenWord;
}

std::vector<std::shared_ptr<Player>> Round::GetPlayers() const noexcept
{
	//RETURNS A VECTOR OF ALL PLAYERS, THE PAINTER BEING AT INDEX 0
	std::vector<std::shared_ptr<Player>> result;
	result.emplace_back(m_painter);
	for (const auto& player : m_players)
		if (player != m_painter)
			result.emplace_back(player);
	return result;
}

void Round::AddPlayer(std::shared_ptr<Player> player)
{
	m_players.emplace_back(player);
}

bool Round::AllGuessersHaveAnswered() const noexcept
{
	return (m_guessTimes.size() == (m_players.size()-1));
}
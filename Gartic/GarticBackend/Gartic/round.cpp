module round;
using namespace gartic;

Player* Round::m_painter = nullptr;
Round::Round(Difficulty newDifficulty, std::vector<Player>* addressOfPlayers):
	m_difficulty{ newDifficulty }, m_players{ addressOfPlayers }, m_miniRoundNumber{ 0 }
{
	/*EMPTY*/;
}

void Round::startRound() noexcept
{
	const int numberOfDifficulties = 2;
	choosePainter();
	++m_miniRoundNumber;
	//Template to changing difficulty between rounds
	if (m_miniRoundNumber - 1 != 0)
	{
		if (m_miniRoundNumber / k_numberOfRounds != (m_miniRoundNumber - 1) / k_numberOfRounds)
		{
			auto difficultyAsInt = GetDifficulty();
			if (difficultyAsInt + 1 <= numberOfDifficulties)
				SetDifficulty(difficultyAsInt + 1);
		}
	}
	//std::string word{ GetHiddenWord() };
	m_startRoundTime = std::chrono::steady_clock::now();
}

void Round::choosePainter() noexcept
{
	auto index_of_new_painter = (m_miniRoundNumber + m_miniRoundNumber / k_numberOfRounds * m_players->size()) % m_players->size();
	m_painter = &(*m_players)[index_of_new_painter];
}

void Round::addPlayerGuessTime(const uint16_t& id)
{
	Time timeNow = std::chrono::steady_clock::now();
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(timeNow - m_startRoundTime).count();
	for (auto& player : *m_players)
	{
		if (player.getID() == id)
		{
			m_guessTimes.emplace_back(&player, seconds);
			return;
		}
	}
	throw std::exception("PLAYER NOT FOUND");
}

void Round::updateScoreForPlayer(Player* player, const uint16_t& seconds = 60) noexcept
{
	if (player == m_painter)
	{
		if (m_guessTimes.empty())
			player->addToScore(-100);
		else
		{
			float average = 0;
			for (auto& item : m_guessTimes)
			{
				average += item.second;
			}
			average /= m_guessTimes.size();
			auto score = (60 - average) * 100 / 60;
			player->addToScore(score);
		}
		return;
	}
	if(seconds==60)
	{
		player->addToScore(-50);
		return;
	}
	if (seconds < 30)
	{
		player->addToScore(100);
		return;
	}
	auto score = (60 - seconds) * 100 / 30;
	player->addToScore(score);
}

uint16_t gartic::Round::DifficultyToInteger(const Difficulty& difficulty) const
{
	switch (difficulty)
	{
	case Difficulty::Easy:
		return 0;
	case Difficulty::Medium:
		return 1;
	case Difficulty::Hard:
		return 2;
	}
	throw std::exception("UNABLE TO CONVERT DIFFICULTY TO INT");
}

Round::Difficulty gartic::Round::IntegerToDifficulty(int difficulty) const
{
	switch (difficulty)
	{
	case 0:
		return Difficulty::Easy;
	case 1:
		return Difficulty::Medium;
	case 2:
		return Difficulty::Hard;
	}
	throw std::exception("UNABLE TO CONVERT INT TO DIFFICULTY");
}

void Round::endRound() noexcept
{
	bool found;
	for (auto& player : *m_players)
	{
		found = false;
		for (auto& item : m_guessTimes)
		{
			if (item.first == &player)
			{
				updateScoreForPlayer(&player, item.second);
				found = true;
				break;
			}
		}
		if(!found)
			updateScoreForPlayer(&player);
	}
	updateScoreForPlayer(m_painter);
	m_guessTimes.clear();
}

bool Round::isWordCorrectAndAddUserGuessTime(const uint16_t& id, const std::string& guess) noexcept
{
	if (guess == m_hiddenWord)
	{
		addPlayerGuessTime(id);
		return true;
	}
	return false;
}

std::string gartic::Round::getWord(const uint16_t& id) const noexcept
{
	if (id == m_painter->getID())
		return m_hiddenWord;
	else
		return m_shownWord;
}

uint16_t Round::getSecondsFromStart() const noexcept
{
	Time timeNow = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(timeNow - m_startRoundTime).count();
}

void gartic::Round::SetDifficulty(int difficultyAsInt)
{
	auto difficulty = IntegerToDifficulty(difficultyAsInt);
	m_difficulty = difficulty;
}

uint16_t gartic::Round::GetDifficulty() const noexcept
{
	return DifficultyToInteger(m_difficulty);
}

void Round::showAllPlayers() const noexcept
{
	for (auto& element : *m_players)
	{
		std::cout << element.getUsername() << " ";
	}
}
module word;

using namespace gartic;

Word::Word(const std::string& word, int difficulty) :
	m_word{ word }, m_difficulty{ difficulty }
{
	/*EMPTY*/
}

void Word::SetWord(const std::string& word) noexcept
{
	m_word = word;
}

void Word::SetDifficulty(int difficulty) noexcept
{
	m_difficulty = difficulty;
}

const std::string& Word::GetWord() const noexcept
{
	return m_word;
}

int Word::GetDifficulty() const noexcept
{
	return m_difficulty;
}

bool Word::operator==(const Word& other) const noexcept
{
	return  m_word == other.GetWord() && m_difficulty == other.GetDifficulty();
}

void Word::operator=(const Word& other)
{
	if (*this == other)
		return;
	m_difficulty = other.m_difficulty;
	m_word = other.m_word;
}

std::ostream& gartic::operator<<(std::ostream& os, const Word& word)
{
	os << word.GetWord() << ' ' << word.GetDifficulty();
	return os;
}
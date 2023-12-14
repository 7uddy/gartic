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

std::ostream& gartic::operator<<(std::ostream& os, const Word& word)
{
	os << word.GetWord() << ' ' << word.GetDifficulty();
	return os;
}
module gamescore;

using namespace gartic;

GameScore::GameScore(int gameID, const std::string& username, float score):
	m_gameID{gameID}, m_username{username}, m_score{score}
{
	/*EMPTY*/
}

void GameScore::SetGameId(const int& gameID) noexcept
{
	m_gameID = gameID;
}

void GameScore::SetUsername(const std::string& username) noexcept
{
	m_username = username;
}

void GameScore::SetScore(const float& score) noexcept
{
	m_score = score;
}

const int& gartic::GameScore::GetGameId() const noexcept
{
	return m_gameID;
}

const std::string& GameScore::GetUsername() const noexcept
{
	return m_username;
}

const float& GameScore::GetScore() const noexcept
{
	return m_score;
}

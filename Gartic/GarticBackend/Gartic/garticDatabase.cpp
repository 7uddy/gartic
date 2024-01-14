#include "garticDatabase.h";

using namespace gartic;

bool GarticDatabase::Initialize()
{
	m_db.sync_schema();
	auto initPlayersCount = m_db.count<Player>();
	if (initPlayersCount == 0)
		PopulatePlayerStorage();
	auto PlayersCount = m_db.count<Word>();


	auto initWordsCount = m_db.count<Word>();
	if (initWordsCount == 0)
		PopulateWordsStorage();
	auto WordsCount = m_db.count<Word>();

	return ((PlayersCount != 0) && (WordsCount != 0));
}

bool GarticDatabase::AddPlayerToDatabase(const std::string& username, const std::string& email, const std::string& password)
{
	try {
		m_db.insert(Player{ username, email, password });
	}
	catch (...)
	{
		return false;
	}
	return true;
}
bool GarticDatabase::DeletePlayerFromDatabase(const std::string& username)
{
	try {
		m_db.remove_all<Player>(sql::where(sql::c(&Player::GetUsername) == username));
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool GarticDatabase::PlayerIsInDatabase(const std::string& username, const std::string& password, const std::string& email)
{
	auto is = m_db.get_all<Player>(sql::where(sql::c(&Player::GetUsername) == username));
	if (is.empty()) return false;
	if (email != "" && is[0].GetEmail() != email) return false;
	if (is[0].GetPassword() != password) return false;
	return true;
}

std::vector<Player> GarticDatabase::GetPlayers()
{
	return m_db.get_all<Player>();
}

std::vector<Word> GarticDatabase::GetWords()
{
	return m_db.get_all<Word>();
}

Word GarticDatabase::GetRandomWordWithDifficulty(int difficulty)
{
	auto generatedNumber = GenerateRandomNumber(kNumberOfWordsOfADifficulty);
	int currentWordNumber{ 0 };
	for (const auto& word : m_db.iterate<Word>())
	{
		if (word.GetDifficulty() != difficulty)
			continue;
		if (++currentWordNumber == generatedNumber)
			return Word{ word };
	}
	return Word{};
}

void GarticDatabase::AddWordToDatabase(const std::string& word, int difficulty)
{
	m_db.insert(Word{ word, difficulty });
}

void GarticDatabase::AddScoreToDatabase(int gameID, const std::string& username, float score)
{
	m_db.insert(GameScore{ gameID,username,score });
}

std::vector<GameScore> GarticDatabase::GetScoresOfPlayer(const std::string& username)
{
	return m_db.get_all<GameScore>(sql::where(sql::c(&GameScore::GetUsername) == username));
}

int GarticDatabase::GetNextGameID()
{
	auto selectStatement = m_db.max(&GameScore::GetGameId);
	if (!selectStatement)
		return 0;
	return (*selectStatement)+1;
}

void GarticDatabase::PopulatePlayerStorage()
{
	std::ifstream fin{ "credentials.txt" };
	if (!fin.is_open())
		throw std::exception("UNABLE TO OPEN FILE TO READ PLAYERS");
	std::string username;
	std::string password;
	std::string email;
	while (fin.good() && fin >> username >> email >> password)
	{
		m_db.insert(Player(username, email, password));
	}
	if (fin.bad())
		throw std::exception("INVALID DATA IN FILE");
	fin.close();
}

void GarticDatabase::PopulateWordsStorage()
{
	std::ifstream fin{ kWordFile };
	if (!fin.is_open())
		throw std::exception("UNABLE TO OPEN FILE TO READ WORDS");
	std::string word; int difficulty;
	while (fin.good() && fin >> word >> difficulty)
	{
		m_db.insert(Word{ word, difficulty });
	}
	if (fin.bad())
		throw std::exception("INVALID DATA IN FILE");
	fin.close();
}

int GarticDatabase::GenerateRandomNumber(int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, max);
	return distrib(gen);
}

#include "Database.h"
#include <fstream>
#include <random>

LoginCredential::LoginCredential(std::string_view argUsername, std::string_view argPassword, std::string_view argEmail)
	: username(argUsername), password(argPassword), email(argEmail)
{
	//Empty
}

Word::Word(const std::string& argWord, const int argDifficulty)
	: word(argWord),
	difficulty(argDifficulty)
{
	//Empty
}

GamesScores::GamesScores(const int& argUserID, const float& argFinalScore)
	:userID(argUserID),
	finalScore(argFinalScore)
{
	//Empty
}

void GetWords(Storage& storage) noexcept
{
	std::ifstream fin{ "words.txt" };
	std::string word; int difficulty;
	while (fin >> word >> difficulty)
	{
		storage.insert(Word(word, difficulty));
	}
	fin.close();
}

int GetRandomDigit(const int& start,const int& maxim) noexcept
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(start, maxim);
	return distrib(gen);

}

int GetNextID(Storage& storage) noexcept
{
	int lastID=-1;
	for (const auto& logincredential : storage.iterate<LoginCredential>())
	{
		lastID = logincredential.userID;
	}
	return lastID;
}

std::string RequestWord(Storage& storage, std::string_view difficulty) noexcept
{
	int firstID = -1, lastID = -1, randomID = -1;

	for (const auto& word : storage.iterate<Word>())
	{
		if (firstID == -1 && std::to_string(word.difficulty) == difficulty)
		{
			firstID = word.wordID;
		}
		if (std::to_string(word.difficulty) == difficulty)
		{
			lastID = word.wordID;
		}
	}
	randomID = GetRandomDigit(firstID, lastID);
	for (const auto& word : storage.iterate<Word>())
	{
		if (word.wordID == randomID)
			return word.word;
	}
	//TODO: Mark the word as used.
}

void GetLoginCredentials(Storage& storage) noexcept
{
	std::ifstream fin{ "credentials.txt" };
	std::string username;
	std::string password;
	std::string email;
	while (fin >> username >> password >> email)
	{
		storage.insert(LoginCredential(username, password, email));
	}
	fin.close();
}
AddUserHandler::AddUserHandler(Storage& storage)
	: m_db{ storage }
{

}

crow::response AddUserHandler::operator()(const crow::request& req) const noexcept
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();

	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");
	auto emailIter = bodyArgs.find("email");

	if (usernameIter != end && passwordIter != end && emailIter != end)
	{
		if (DoesUsernameExists(usernameIter->second) || DoesEmailExists(emailIter->second))
		{
			LoginCredential userCredential(usernameIter->second, passwordIter->second, emailIter->second);
			m_db.insert(userCredential);
			return crow::response(200);
		}
		else return crow::response(400);
	}
}

bool AddUserHandler::DoesUsernameExists(std::string_view username) const noexcept
{
	auto count = m_db.count<LoginCredential>(sql::where(sql::c(&LoginCredential::username) == username));
	return count > 0;
}

bool AddUserHandler::DoesEmailExists(std::string_view email) const noexcept
{
	auto count = m_db.count<LoginCredential>(sql::where(sql::c(&LoginCredential::email) == email));
	return count>0;
}


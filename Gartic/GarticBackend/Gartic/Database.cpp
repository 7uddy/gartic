#include "Database.h"
#include <fstream>

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

void getWords(Storage& storage)
{
	std::ifstream fin{ "words.txt" };
	std::string word; int difficulty;
	while (fin >> word >> difficulty)
	{
		storage.insert(Word(word, difficulty));
	}
	fin.close();
}

void getLoginCredentials(Storage& storage)
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


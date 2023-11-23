#include "Database.h"
#include <fstream>

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

crow::response AddUserHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();

	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");
	auto emailIter = bodyArgs.find("email");

	if (usernameIter != end && passwordIter != end && emailIter != end)
	{
		LoginCredential userCredential(usernameIter->second, passwordIter->second, emailIter->second);
		m_db.insert(userCredential);
	}
	return crow::response(200);
}

bool AddUserHandler::DoesUsernameExists(const std::string& username) const
{
	auto count = m_db.count<LoginCredential>(sql::where(sql::c(&LoginCredential::username) == username));
	return count > 0;
}

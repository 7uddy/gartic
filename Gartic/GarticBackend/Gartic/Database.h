#pragma once
#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

import utils;

class LoginCredential
{

public:
	LoginCredential() = default;
	LoginCredential(std::string_view argUsername, std::string_view argPassword, std::string_view argEmail);


	int userID;
	std::string username;
	std::string password;
	std::string email;

};


class Word
{

public:
	Word() = default;
	Word(const std::string& argWord, const int argDifficulty);

	int wordID;
	std::string word;
	int difficulty;

};

class GamesScores
{

public:
	GamesScores() = default;
	GamesScores(const int& argUserID, const float& argFinalScore);

	int gameID;
	int userID;
	float finalScore;

};

inline auto CreateStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"LoginCredentials",
			sql::make_column("userID", &LoginCredential::userID, sql::primary_key().autoincrement()),
			sql::make_column("username", &LoginCredential::username),
			sql::make_column("password", &LoginCredential::password),
			sql::make_column("email", &LoginCredential::email)
			),
		sql::make_table(
			"Words",
			sql::make_column("wordID", &Word::wordID, sql::primary_key().autoincrement()),
			sql::make_column("word", &Word::word),
			sql::make_column("difficulty", &Word::difficulty)
		),
		sql::make_table(
			"GamesScores",
			sql::make_column("gameID", &GamesScores::gameID, sql::primary_key()),
			sql::make_column("userID", &GamesScores::userID),
			sql::make_column("finalScore", &GamesScores::finalScore),
			sql::foreign_key(&GamesScores::userID).references(&LoginCredential::userID)
		)

	);
}

using Storage = decltype(CreateStorage(""));
void GetLoginCredentials(Storage& storage) noexcept;
void GetWords(Storage& storage) noexcept;
int GetNextID(Storage& storage) noexcept;
std::string RequestWord(Storage& storage,std::string_view difficulty) noexcept;
int GetRandomDigit(const int& start, const int& maxim) noexcept;



class AddUserHandler {

public:
	AddUserHandler(Storage& storage);
	bool DoesUsernameExists(std::string_view username) const noexcept;
	bool DoesEmailExists(std::string_view email) const noexcept;
	crow::response operator() (const crow::request& req) const noexcept;

private:
	Storage& m_db;
};

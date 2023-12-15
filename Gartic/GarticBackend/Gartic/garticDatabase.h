#pragma once

#include <crow.h>
#include <filesystem>
#include <memory>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

import player;
import word;

//import <string>;
//import <iostream>;
import <fstream>;
import <vector>;
import <random>;

namespace gartic
{
	inline auto CreateStorage(const std::string& filename)
	{
		return sql::make_storage(
			filename,
			sql::make_table(
				"Players",
				sql::make_column("username", &Player::SetUsername, &Player::GetUsername, sql::unique()),
				sql::make_column("email", &Player::SetEmail, &Player::GetEmail,sql::unique()),
				sql::make_column("password", &Player::SetPassword, &Player::GetPassword)
			),
			sql::make_table(
				"Words",
				sql::make_column("word", &Word::SetWord, &Word::GetWord, sql::unique()),
				sql::make_column("difficulty", &Word::SetDifficulty, &Word::GetDifficulty)
			)
		);
	}

	using Storage = decltype(CreateStorage(""));


	class GarticDatabase
	{
	public:
		bool Initialize() ;

		bool AddPlayerToDatabase(std::string username, std::string email, std::string password);
		bool DeletePlayerFromDatabase(std::string username);
		bool PlayerIsInDatabase(std::string username, std::string password,std::string email="");
		std::vector<Player> GetPlayers();

		std::vector<Word> GetWords();
		Word GetRandomWordWithDifficulty(int difficulty);
		void AddWordToDatabase(std::string word, int difficulty);
		
	private:
		void PopulatePlayerStorage();
		void PopulateWordsStorage();
		int GenerateRandomNumber(int max);

	private:
		const std::string kDbFile{ "database.sqlite" };
		const std::string kWordFile{ "words.txt" };
		const int kNumberOfWordsOfADifficulty = 166; // 500 / 3

	private:
		Storage m_db = CreateStorage(kDbFile);
	};
}
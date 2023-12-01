#include <filesystem>
#include <iostream>
#include <memory>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;


#include "Database.h"
import game;
import lobby;

int main()
{
	const std::string db_file = "logincredentials.sqlite";
	Storage db = createStorage(db_file);
	db.sync_schema();
	auto initLoginCredentialCount = db.count<LoginCredential>();
	if (initLoginCredentialCount == 0)
		getLoginCredentials(db);

	auto initWords = db.count<Word>();
	if (initWords == 0)
		getWords(db);

	auto loginCredentialCount = db.count<LoginCredential>();
	std::cout << "## There are currently " << loginCredentialCount << " items in the database.##\n";
	crow::SimpleApp app;
	CROW_ROUTE(app, "/")([]() {
		return "Server is running.This is the main branch";
		});

	CROW_ROUTE(app, "/logincredentials")([&db]() {
		std::vector<crow::json::wvalue> logincredentials_json;
		for (const auto& logincredential : db.iterate<LoginCredential>())
		{
			logincredentials_json.push_back(crow::json::wvalue{ 
				{"userID", logincredential.userID}, 
				{"username", logincredential.username},
				{"password", logincredential.password},
				{"email", logincredential.email}
				});			
		}
		return crow::json::wvalue{ logincredentials_json };
		});

	auto& addToDatabaseUser = CROW_ROUTE(app, "/addusertodatabase")
		.methods(crow::HTTPMethod::PUT);
	addToDatabaseUser(AddUserHandler(db));

	CROW_ROUTE(app, "/verifyuserindatabase")
		.methods(crow::HTTPMethod::GET)([&db](const crow::request& req)
			{
				std::string receivedUsername = req.url_params.get("username");
				std::string receivedPassword = req.url_params.get("password");
				std::string receivedEmail = req.url_params.get("email");

				if(receivedPassword.empty())
					return crow::response(400);
				if(receivedUsername.empty() && receivedEmail.empty())
					return crow::response(400);

				if(!receivedUsername.empty())
					for (const auto& logincredential : db.iterate<LoginCredential>())
					{
						if (logincredential.username == receivedUsername
							&& logincredential.password == receivedPassword)
							return crow::response(302);
					}
				else
					for (const auto& logincredential : db.iterate<LoginCredential>())
					{
						if (logincredential.email == receivedEmail
							&& logincredential.password == receivedPassword)
							return crow::response(302);
					}
				return crow::response(404);
			});

	CROW_ROUTE(app, "/deleteuserfromdatabase")
		.methods(crow::HTTPMethod::GET)([&db](const crow::request& req)
			{
				std::string receivedUsername = req.url_params.get("username");
				if (receivedUsername.empty())
					return crow::response(400);

				else {
					db.remove_all<LoginCredential>(sql::where(sql::c(&LoginCredential::username) == receivedUsername));
					return crow::response(200);
				}
				return crow::response(404);
			});
	app.port(18080).multithreaded().run();
	return 0;
}
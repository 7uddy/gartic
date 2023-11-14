#include "Game.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include"Database.h"
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

int main()
{
	const std::string db_file = "logincredentials.sqlite";
	Storage db = createStorage(db_file);
	db.sync_schema();
	auto initLoginCredentialCount = db.count<LoginCredential>();
	if (initLoginCredentialCount == 0)
		populateStorage(db);
	auto loginCredentialCount = db.count<LoginCredential>();
	std::cout << "productsCount = " << loginCredentialCount << '\n';
	crow::SimpleApp app;
	CROW_ROUTE(app, "/")([]() {
		return "Server is running.This is the main branch";
		});
	CROW_ROUTE(app, "/logincredentials")([&db]() {
		std::vector<crow::json::wvalue> logincredentials_json;
		for (const auto& logincredential : db.iterate<LoginCredential>())
		{
			logincredentials_json.push_back(crow::json::wvalue{
				{"userID", logincredential.userID},  // logincredentials_json["userID"] = logincredential.userID;
				{"username", logincredential.username},
				{"password", logincredential.password},
				{"email", logincredential.email}
				});

			//std::string product_json = db.dump(product);			
		}
		return crow::json::wvalue{ logincredentials_json };
		});
	app.port(18080).multithreaded().run();
	return 0;
}
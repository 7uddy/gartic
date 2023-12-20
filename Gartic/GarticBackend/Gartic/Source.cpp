#include <crow.h>
#include "garticDatabase.h"
#include "routing.h"
import lobby;
using namespace gartic;

//OLD CODE
//Storage CreateDatabase() 
//{
//	const std::string db_file = "logincredentials.sqlite";
//	Storage db = CreateStorage(db_file);
//	db.sync_schema();
//	auto initLoginCredentialCount = db.count<LoginCredential>();
//	if (initLoginCredentialCount == 0)
//		GetLoginCredentials(db);
//
//	auto initWords = db.count<Word>();
//	if (initWords == 0)
//		GetWords(db);
//
//	auto loginCredentialCount = db.count<LoginCredential>();
//	std::cout << "## There are currently " << loginCredentialCount << " items in the database.##\n";
//	return db;
//}
//
//void ServerRoutes(GarticDatabase& db, crow::SimpleApp& app)
//{
//	CROW_ROUTE(app, "/")([]() {
//		return "Server is running.This is the main branch";
//		});
//
//	CROW_ROUTE(app, "/logincredentials")([&db]() {
//		std::vector<crow::json::wvalue> logincredentials_json;
//		auto players = db.GetPlayers();
//		for (const auto& logincredential : players)
//		{
//			logincredentials_json.push_back(crow::json::wvalue{
//				{"username", logincredential.GetUsername()},
//				{"password", logincredential.GetPassword()},
//				{"email", logincredential.GetEmail()}
//				});
//		}
//		return crow::json::wvalue{ logincredentials_json };
//		});
//
//	CROW_ROUTE(app, "/register")
//		.methods(crow::HTTPMethod::PUT)([&db](const crow::request& req)
//			{
//				std::string receivedUsername = req.url_params.get("username");
//				std::string receivedPassword = req.url_params.get("password");
//				std::string receivedEmail = req.url_params.get("email");
//
//				if (receivedUsername.empty() || receivedEmail.empty() || receivedPassword.empty())
//					return crow::response(400);
//				
//				if (!db.PlayerIsInDatabase(receivedUsername, receivedPassword, receivedEmail))
//				{
//					if (db.AddPlayerToDatabase(receivedUsername, receivedEmail, receivedPassword))
//						return crow::response(201);
//				}
//				else return crow::response(406);
//
//			});
//
//	CROW_ROUTE(app, "/verifyuser")
//		.methods(crow::HTTPMethod::GET)([&db](const crow::request& req)
//			{
//				std::string receivedUsername = req.url_params.get("username");
//				std::string receivedPassword = req.url_params.get("password");
//				std::string receivedEmail = req.url_params.get("email");
//
//				if (receivedPassword.empty() || receivedUsername.empty() || receivedEmail.empty())
//					return crow::response(400);
//
//				if(db.PlayerIsInDatabase(receivedUsername,receivedPassword,receivedEmail))
//					return crow::response(302);
//				
//				return crow::response(404);
//			});
//
//	CROW_ROUTE(app, "/login")
//		.methods(crow::HTTPMethod::GET)([&db](const crow::request& req)
//			{
//				std::string receivedUsername = req.url_params.get("username");
//				std::string receivedPassword = req.url_params.get("password");
//
//				if (receivedPassword.empty() || receivedUsername.empty())
//					return crow::response(400);
//
//				if (db.PlayerIsInDatabase(receivedUsername,receivedPassword))
//					return crow::response(202);
//
//				return crow::response(404);
//			});
//
//	    CROW_ROUTE(app, "/deleteuser")
//		.methods(crow::HTTPMethod::GET)([&db](const crow::request& req)
//			{
//				std::string receivedUsername = req.url_params.get("username");
//				
//				if (receivedUsername.empty())
//					return crow::response(400);
//
//				else {
//					db.DeletePlayerFromDatabase(receivedUsername);
//					return crow::response(202);
//				}
//				return crow::response(404);
//			});
//
//	gartic::Lobby lobby;
//
//	CROW_ROUTE(app, "/join")
//		.methods(crow::HTTPMethod::GET)([&lobby, &db](const crow::request& req)
//			{
//				std::string receivedLobbyID = req.url_params.get("lobbyid");
//				std::string receivedUserID = req.url_params.get("username");
//
//				if (receivedLobbyID.empty() || receivedUserID.empty())
//					return crow::response(400);
//
//				else {
//					if (lobby.GetLobbyCode() == receivedLobbyID)
//					{
//						std::unique_ptr<Player> player = std::make_unique<Player>(receivedUserID, "", "");
//						try {
//							lobby.AddPlayer(player);
//							return crow::response(200);
//						}
//						catch (...)
//						{
//							return crow::response(400);
//						}
//						/*for (const auto& logincredential : db.iterate<LoginCredential>())
//						{
//							if (std::to_string(logincredential.userID) == receivedUserID)
//							{
//								gartic::Player newPlayer(logincredential.username, logincredential.password,logincredential.email,logincredential.userID);
//								lobby.addPlayer(std::move(newPlayer));
//								return crow::response(200);
//							}
//						}*/
//					}
//				}
//				return crow::response(404);
//			});
//}

int main()
{
	GarticDatabase storage;
	if (!storage.Initialize())
	{
		std::cout << "Faild to initialize the database!";
		return -1;
	}
	/*for (const auto& word : storage.GetWords())
		std::cout << word << ' ';*/
	std::unique_ptr<Game> game; /*std::make_unique<Game>();
	game->AddPlayerToGame(std::make_unique<Player>("andrei", "email", ""));
	game->StartAnotherRound();*/
	std::unique_ptr<Lobby> lobby/* = std::make_unique<Lobby>()*/;
	Routing r;
	r.Run(storage, game, lobby);
	r.GetApp().port(18080).multithreaded().run();
	return 0;
}
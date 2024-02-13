#include "../../Gartic/includes/routing.h"

import lobby;
import <unordered_set>;

using namespace gartic;


//TO DO:
//convert methods related to game status to static
//create new routes related to game ending
//create new routes related to timer, get hidden word, get hint and start another round
//modify methods related to chat>?<

void Routing::Run(GarticDatabase& db, std::unique_ptr<Game>& game, std::unordered_map<std::string, std::unique_ptr<Lobby>>& lobbies, std::unordered_set<std::string>& loggedInPlayers)
{

	CROW_ROUTE(m_app, "/")([]() {
		return "Server is running.This is the main branch";
		});

	CROW_ROUTE(m_app, "/logincredentials")([&db]() {
		std::vector<crow::json::wvalue> logincredentials_json;
		auto players = db.GetPlayers();
		for (const auto& logincredential : players)
		{
			logincredentials_json.push_back(crow::json::wvalue{
				{"username", logincredential.GetUsername()},
				{"password", logincredential.GetPassword()},
				{"email", logincredential.GetEmail()}
				});
		}
		return crow::json::wvalue{ logincredentials_json };
		});

	CROW_ROUTE(m_app, "/register")
		.methods(crow::HTTPMethod::PUT)([&db](const crow::request& req)
			{
				std::string receivedUsername{ req.url_params.get("username") };
				std::string receivedPassword{ req.url_params.get("password") };
				std::string receivedEmail { req.url_params.get("email") };

				if (receivedUsername.empty() || receivedEmail.empty() || receivedPassword.empty())
					return crow::response(400);

				if (!db.PlayerIsInDatabase(receivedUsername, receivedPassword, receivedEmail))
				{
					if (db.AddPlayerToDatabase(receivedUsername, receivedEmail, receivedPassword))
						return crow::response(201);
				}
				return crow::response(406);

			});

	CROW_ROUTE(m_app, "/verifyuser")
		.methods(crow::HTTPMethod::GET)([&db](const crow::request& req)
			{
				std::string receivedUsername { req.url_params.get("username") };
				std::string receivedPassword { req.url_params.get("password") };
				std::string receivedEmail { req.url_params.get("email") };

				if (receivedPassword.empty() || receivedUsername.empty() || receivedEmail.empty())
					return crow::response(400);

				if (db.PlayerIsInDatabase(receivedUsername, receivedPassword, receivedEmail))
					return crow::response(302);

				return crow::response(404);
			});

	CROW_ROUTE(m_app, "/login")
		.methods(crow::HTTPMethod::GET)([&db, &lobbies, &loggedInPlayers, &game](const crow::request& req)
			{
				//CHECK DATA
				std::string receivedUsername { req.url_params.get("username") };
				std::string receivedPassword { req.url_params.get("password") };

				if (receivedPassword.empty() || receivedUsername.empty())
					return crow::response(400);

				//CHECK DATA IN DATABASE
				if (!db.PlayerIsInDatabase(receivedUsername, receivedPassword))
					return crow::response(404);

				//CHECK IF PLAYER IS ALREADY LOGGED IN
				if (auto foundPlayer = loggedInPlayers.contains(receivedUsername); foundPlayer)
					return crow::response(409);

				//CHECK IF PLAYER IS IN GAME
				if (game)
				{
					if (game->IsPlayerInGame(receivedUsername))
						return crow::response(409);
				}

				//ADD PLAYER TO LOGGED PLAYERS SET
				loggedInPlayers.insert(receivedUsername);

				return crow::response(202);
			});

	CROW_ROUTE(m_app, "/disconnect")
		.methods(crow::HTTPMethod::GET)([&loggedInPlayers](const crow::request& req)
			{
				std::string receivedUsername{ req.url_params.get("username") };

				//CHECK DATA
				if (receivedUsername.empty())
					return crow::response(400);

				loggedInPlayers.erase(receivedUsername);

				return crow::response(409);
			});


	CROW_ROUTE(m_app, "/deleteuser")
		.methods(crow::HTTPMethod::GET)([&db](const crow::request& req)
			{
				std::string receivedUsername { req.url_params.get("username") };

				if (receivedUsername.empty())
					return crow::response(400);

				else {
					db.DeletePlayerFromDatabase(receivedUsername);
					return crow::response(202);
				}
				return crow::response(404);
			});

	//ROUTES RELATED TO LOBBY
	CROW_ROUTE(m_app, "/createlobby")
		.methods(crow::HTTPMethod::GET)([&lobbies, &loggedInPlayers](const crow::request& req)
			{
				//CHECK DATA
				std::string receivedUsername { req.url_params.get("username") };
				if (receivedUsername.empty())
					return crow::json::wvalue{ {"text", "ERROR: NO USERNAME"} };

				//CHECK IF PLAYER IS LOGGED IN
				if (!loggedInPlayers.contains(receivedUsername))
					return crow::json::wvalue{ {"text", "ERROR: PLAYER NOT LOGGED IN"} };

				//CREATE NEW LOBBY AND ADD PLAYER TO LOBBY
				std::unique_ptr<Lobby> lobby = std::make_unique<Lobby>();
				std::unique_ptr<Player> player = std::make_unique<Player>(receivedUsername);
				lobby->AddPlayer(player);

				//GET LOBBY CODE TO BE SENT
				std::string lobbyCode{ lobby->GetLobbyCode() };

				//ADD LOBBY TO LOBBIES MAP
				lobbies.emplace(std::make_pair(lobby->GetLobbyCode(), std::move(lobby)));

				//RETURN LOBBY CODE
				return crow::json::wvalue{ {"text", lobbyCode} };
			});

	
	CROW_ROUTE(m_app, "/joinlobby")
		.methods(crow::HTTPMethod::GET)([&lobbies, &loggedInPlayers](const crow::request& req)
			{
				std::string receivedLobbyCode = req.url_params.get("lobbycode");
				std::string receivedUsername { req.url_params.get("username") };

				//CHECK DATA
				if (receivedLobbyCode.empty() || receivedUsername.empty())
					return crow::response(400);

				//CHECK IF PLAYER IS LOGGED IN
				if (!loggedInPlayers.contains(receivedUsername))
					return crow::response(405);

				//THRWOS UNEXPECTED ERROR IF THERE IS NO LOBBY WITH CODE
				//CHECK IF THERE IS A LOBBY WITH LOBBYCODE
				auto& foundLobby = lobbies.at(receivedLobbyCode);
				if (foundLobby==nullptr)
					return crow::response(400);

				//CHECK IF THERE ARE 4 PLAYERS ALREADY IN LOBBY
				if (foundLobby->GetNumberOfPlayers() == 4)
					return crow::response(405);

				try
				{
					//TRY ADDING PLAYER
					std::unique_ptr<Player> player = std::make_unique<Player>(receivedUsername);
					foundLobby->AddPlayer(player);
					return crow::response(200);
				}
				catch (...)
				{
					//THERE IS ALREADY A PLAYER WITH THAT USERNAME IN LOBBY WITH LOBBYCODE
					return crow::response(409);
				}
			});

	
	//CAN MODIFY TO RECEIVE USERNAME -AND- LOBBYCODE TO BYPASS SEARCHING FOR LOBBY
	CROW_ROUTE(m_app, "/disconnectfromlobby")
		.methods(crow::HTTPMethod::GET)([&lobbies](const crow::request& req)
			{
				std::string receivedUsername { req.url_params.get("username") };

				//CHECK DATA
				if (receivedUsername.empty())
					return crow::response(400);

				//FIND LOBBY WITH PLAYER
				for (auto& lobby : lobbies)
				{
					//IF NOT CORRECT LOBBY, SKIP
					if (!lobby.second->IsInLobby(receivedUsername))
						continue;

					//TRY REMOVING PLAYER FROM FOUND LOBBY
					try
					{
						//REMOVE PLAYER FROM LOBBY
						lobby.second->RemovePlayer(receivedUsername);
						//DELETE LOBBY IF NO PLAYERS ARE IN IT
						if (lobby.second->GetNumberOfPlayers() == 0)
						{
							lobbies.erase(lobby.first);

							/*lobbies.erase(std::remove_if(lobbies.begin(), lobbies.end(),
								[&](const std::unique_ptr<Lobby>& ptr) {
									return ptr.get() == foundLobby->get();
								}));*/
						}
						return crow::response(200);
					}
					catch (...)
					{

						return crow::response(409);
					}
				}

				return crow::response(409);
			});

	

	CROW_ROUTE(m_app, "/getlobbystatus")
		.methods(crow::HTTPMethod::GET)([&lobbies](const crow::request& req)
			{
				std::string receivedLobbyCode = req.url_params.get("lobbycode");

				//CHECK DATA
				if (receivedLobbyCode.empty())
					return crow::json::wvalue{ "ERROR: NO LOBBYCODE IN PARAMETERS" };

				//CHECK IF THERE IS A LOBBY WITH LOBBYCODE
				if(!lobbies.contains(receivedLobbyCode))
					return crow::json::wvalue{ "ERROR: NO LOBBY WITH LOBBYCODE" };

				//SHOULD BE MOVED TO ANOTHER ROUTE
				auto& foundLobby = lobbies[receivedLobbyCode];

				//SHOULD HAVE A STATIC METHOD
				auto status = foundLobby->GetStatusOfLobby();
				if (status == foundLobby->ConvertStatusToInteger(Lobby::Status::Launched))
					foundLobby->AddRequestForEnd();

				if (foundLobby->TimeToDeleteLobby())
				{
					//DELETE LOBBY
					lobbies.erase(receivedLobbyCode);
					/*lobbies.erase(std::remove_if(lobbies.begin(), lobbies.end(),
					[&](const std::unique_ptr<Lobby>& ptr) {
						return ptr.get() == foundLobby->get();
					}));*/
				}
				//

				return crow::json::wvalue{ status };
			});


	
	CROW_ROUTE(m_app, "/getusernamesfromlobby")
		.methods(crow::HTTPMethod::GET)([&lobbies](const crow::request& req)
			{
				//CHECK DATA
				std::string receivedLobbyCode = req.url_params.get("lobbycode");
				if (receivedLobbyCode.empty())
					return crow::json::wvalue{ "ERROR: NO LOBBY CODE IN PARAMETERS" };

				//CHECK IF LOBBY EXISTS
				if(!lobbies.contains(receivedLobbyCode))
					return crow::json::wvalue{ "ERROR: NO LOBBY WITH LOBBYCODE" };

				//FIND LOBBY WITH LOBBYCODE 
				auto& foundLobby = lobbies[receivedLobbyCode];

				//GET DATA OF PLAYERS
				std::vector<crow::json::wvalue> gameData_json;
				auto playersUsername = foundLobby->GetUsernamesOfPlayers();
				for (const auto& username : playersUsername)
				{
					gameData_json.push_back(crow::json::wvalue{
						{"username", username}
						});
				}
				return crow::json::wvalue{ gameData_json };
			});

	
	CROW_ROUTE(m_app, "/startgame")
		.methods(crow::HTTPMethod::GET)([&lobbies, &game, &db](const crow::request& req)
			{
				//CHECK DATA
				std::string receivedLobbyCode = req.url_params.get("lobbycode");
				std::string receivedDifficulty = req.url_params.get("difficulty");
				if (receivedLobbyCode.empty() || receivedDifficulty.empty())
					return crow::response(400);

				int difficulty = std::stoi(receivedDifficulty);
				if (difficulty < 0 || difficulty>3)
					return crow::response(400);

				//CHECK IF THERE IS ALREADY A GAME RUNNING
				if (game)
					return crow::response(409);

				//CHECK IF THERE EXISTS LOBBY WITH LOBBYCODE
				if (!lobbies.contains(receivedLobbyCode))
					return crow::response(400);

				//FIND LOBBY WITH LOBBYCODE 
				auto& foundLobby = lobbies[receivedLobbyCode];

				//CHECK IF THERE IS ONLY ONE PLAYER IN LOBBY
				if (foundLobby->GetNumberOfPlayers() < 2)
					return crow::response(405);

				//START GAME
				//SET DIFFICULTY OF GAME
				try
				{
					game = std::make_unique<Game>(db.GetNextGameID());
					game->ChangeDifficulty(difficulty);
					game->SetStatusOfGame(Game::Status::Active);

					//MOVE PLAYERS FROM LOBBY TO GAME
					foundLobby->MovePlayersToGame(*(game.get()));

					//START FIRST ROUND
					game->StartAnotherRound(db);
				}
				catch (...)
				{
					return crow::response(405);
				}

				return crow::response(200);
			});


	//ROUTES RELATED TO GAME

	CROW_ROUTE(m_app, "/getgamestatus")
		.methods(crow::HTTPMethod::GET)([&game](const crow::request& req)
			{
				//CHECK IF THERE EXISTS A GAME
				if(!game)
					return crow::json::wvalue{ "" };
				return crow::json::wvalue{ game->GetGameStatus()};
			});

	CROW_ROUTE(m_app, "/getplayersdatafromgame")
		.methods(crow::HTTPMethod::GET)([&game]() 
			{
				if (!game)
					return crow::json::wvalue{ "" };
				std::vector<crow::json::wvalue> gameData_json;
				auto players = game->GetPlayers();
				for (const auto& player : players)
				{
					gameData_json.push_back(crow::json::wvalue{
						{"username", player->GetUsername()},
						{"score", std::to_string(player->GetScore())}
						});
				}
				return crow::json::wvalue{ gameData_json };
			});

	CROW_ROUTE(m_app, "/addmessagetochat")
		.methods(crow::HTTPMethod::GET)([&game](const crow::request& req)
			{
				//CHECK DATA
				std::string receivedUsername { req.url_params.get("username") };
				std::string receivedMessage = req.url_params.get("message");
				if (receivedUsername.empty() || receivedMessage.empty())
					return crow::response(400);
				//CHECK IF THERE IS A GAME
				if (!game)
					return crow::response(404);
				//ADD MESSAGES TO CHAT
				//If message is hidden word, return that the player has guessed the word
				if (game->AddMessageToChat(std::move(receivedMessage), std::move(receivedUsername)))
					return crow::response(201);
				//Return success
				return crow::response(200);
			});

	CROW_ROUTE(m_app, "/getchat")
		.methods(crow::HTTPMethod::GET)([&game](const crow::request& req) 
			{
				//CHECK DATA
				if (!game)
					return crow::json::wvalue{ "" };
				std::string receivedUsername { req.url_params.get("username") };
				if (receivedUsername.empty())
					return crow::json::wvalue{ "ERROR: NO USERNAME IN PARAMETERS" };

				//GET CHAT
				std::vector<crow::json::wvalue> gameData_json;
				auto messages = game->GetChat(std::move(receivedUsername));
				for (const auto& message : messages)
				{
					gameData_json.push_back(crow::json::wvalue{
						{"message", message}
						});
				}
				return crow::json::wvalue{ gameData_json };
			});

	CROW_ROUTE(m_app, "/getroundnumber")
		.methods(crow::HTTPMethod::GET)([&game](const crow::request& req)
			{
				if (!game)
					return crow::json::wvalue{ "" };
				return crow::json::wvalue{ game->GetRoundNumber() };
			});

	CROW_ROUTE(m_app, "/gettimer")
		.methods(crow::HTTPMethod::GET)([&game, &db](const crow::request& req)
			{
				if (!game)
					return crow::json::wvalue{ "" };
				game->IsTimeForHint();
				auto seconds = game->GetTimer();
				if (game->GetGameStatus() == Game::ConvertStatusToInteger(Game::Status::Transitioning))
					return crow::json::wvalue{ Round::kRoundSeconds };
				if ((seconds > Round::kRoundSeconds || game->AllPlayersGuessed()))
					game->StartAnotherRound(db);
				return crow::json::wvalue{ game->GetTimer() };
			});

	CROW_ROUTE(m_app, "/getboard")
		.methods(crow::HTTPMethod::GET)([&game](const crow::request& req)
			{
				if (!game)
					return crow::json::wvalue{ "" };
				std::vector<crow::json::wvalue> gameData_json;
				auto coordinates = game->GetBoard();
				for (const auto& coordinate : coordinates)
				{
					gameData_json.push_back(crow::json::wvalue{
						{"x", std::to_string(coordinate.first)},
						{"y", std::to_string(coordinate.second)}
						});
				}
				return crow::json::wvalue{ gameData_json };
			});

	CROW_ROUTE(m_app, "/sendboard")
		.methods(crow::HTTPMethod::GET)([&game](const crow::request& req)
			{
				if (req.body.empty()) 
					return crow::response(400);
				if (!game)
					return crow::response(404);
				auto jsonBody = crow::json::load(req.body);
				int x{}, y{};
				std::vector<Game::Coordinate> receivedCoordinates;
				for (const auto& coordinateJson : jsonBody) {
					x = coordinateJson["x"].i();
					y = coordinateJson["y"].i();
					receivedCoordinates.emplace_back(x, y);
				}

				if (game->GetGameStatus() == Game::ConvertStatusToInteger(Game::Status::Transitioning))
					return crow::response(200);

				game->UpdateBoard(std::move(receivedCoordinates));
				return crow::response(200);
			});

	CROW_ROUTE(m_app, "/getword")
		.methods(crow::HTTPMethod::Get)([&game](const crow::request& req)
			{
				if (!game)
					return crow::json::wvalue{ "" };
				std::string receivedUsername { req.url_params.get("username") };
				if (receivedUsername.empty())
					return crow::json::wvalue{ "ERROR: NO USERNAME IN PARAMETERS" };
				//CHECK IF THERE IS A GAME
				if (!game)
					return crow::json::wvalue{ "ERROR: NO GAME IN PROGRESS." };
				if (receivedUsername == game->GetPainterUsername())
				{
					return crow::json::wvalue{ {"Word", game->GetHiddenWord()} };
				}
				else
				{
					return crow::json::wvalue{ {"Word", game->GetShownWord()} };
				}
			});

	//ROUTE RELATED TO END GAME
	CROW_ROUTE(m_app, "/getplayersandrequestend")
		.methods(crow::HTTPMethod::GET)([&game, &db]() 
			{
				if (!game)
					return crow::json::wvalue{ "" };
				if (game->GetGameStatus() != game->ConvertStatusToInteger(Game::Status::Finished))
				{
					return crow::json::wvalue{ "ERROR: GAME HAS NOT FINISHED" };
				}

				std::vector<crow::json::wvalue> gameData_json;
				auto players = game->GetPlayers();

				std::ranges::sort(players, [](const std::shared_ptr<Player>& p1, const std::shared_ptr<Player>& p2) {
					return p1->GetScore() > p2->GetScore();
					});

				for (const auto& player : players)
				{
					gameData_json.push_back(crow::json::wvalue{
						{"username", player->GetUsername()},
						{"score", std::to_string(player->GetScore())}
						});
				}

				game->AddRequestForEnd();
				if (game->TimeToEndGame())
				{
					game->SaveScoresInDatabase(db);
					game.reset();
				}

				return crow::json::wvalue{ gameData_json };
			});

	CROW_ROUTE(m_app, "/disconnectfromgame")
		.methods(crow::HTTPMethod::GET)([&game](const crow::request& req)
			{
				std::string receivedUsername{ req.url_params.get("username") };

				//CHECK DATA
				if (receivedUsername.empty())
					return crow::response(400);
				try 
				{
					game->RemovePlayer(receivedUsername);

				}
				catch (...)
				{
					return crow::response(409);
				}
				return crow::response(200);
			});

	//PROFILE PAGE
	CROW_ROUTE(m_app, "/getgamescores")
		.methods(crow::HTTPMethod::Get)([&db, &loggedInPlayers](const crow::request& req)
			{
				//CHECK DATA
				std::string receivedUsername { req.url_params.get("username") };
				if (receivedUsername.empty())
					return crow::json::wvalue{ "ERROR: NO USERNAME IN PARAMETERS" };

				//CHECK IF PLAYER IS LOGGED IN
				if(!loggedInPlayers.contains(receivedUsername))
					return crow::json::wvalue{ "ERROR: USER NOT LOGGED IN" };

				//GET GAME DATA
				std::vector<crow::json::wvalue> gameData_json;
				auto scores = db.GetScoresOfPlayer(receivedUsername);
				for (const auto& score : scores)
				{
					gameData_json.push_back(crow::json::wvalue{
						{"gameid", std::to_string(score.GetGameId())},
						{"score", std::to_string(score.GetScore())}
						});
				}
				return crow::json::wvalue{ gameData_json };
			});

}

crow::SimpleApp& Routing::GetApp()
{
	return m_app;
}

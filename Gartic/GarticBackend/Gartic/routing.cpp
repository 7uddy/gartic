#include "routing.h"

import lobby;
using namespace gartic;

//SHOULD BE MOVED TO UTILS?
auto GetLobbyWithPlayer(const std::vector<std::unique_ptr<Lobby>>& lobbies, std::string_view username)
{
	for (const auto& lobby : lobbies)
		if (lobby->IsInLobby(std::string{ username }))
			return &lobby;
	const std::unique_ptr<Lobby> nullp;
	return &nullp;
	/*auto foundLobby = std::find(lobbies.begin(), lobbies.end(), [&username](std::unique_ptr<Lobby>& currentLobby)
		{
			return currentLobby->IsInLobby(std::string{ username });
		});
	return &(*foundLobby);*/
}

auto GetLobbyWithCode(const std::vector<std::unique_ptr<Lobby>>& lobbies, std::string_view lobbyCode)
{
	for (const auto& lobby : lobbies)
		if (lobby->CheckLobbyCode(std::string{ lobbyCode }))
			return &lobby;
	const std::unique_ptr<Lobby> nullp;
	return &nullp;

}

void Routing::Run(GarticDatabase& db, std::unique_ptr<Game>& game, std::vector<std::unique_ptr<Lobby>>& lobbies)
{
	//IF MULTIPLE LOBBIES ARE ALLOWED -> lobby SHOULD BE CHANGED TO vector of LOBBY AND ALL RESPECTIVE ROUTES
	//getelement => send element from server to client
	//sendelement => send element from client to server
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
				std::string receivedUsername = req.url_params.get("username");
				std::string receivedPassword = req.url_params.get("password");
				std::string receivedEmail = req.url_params.get("email");

				if (receivedUsername.empty() || receivedEmail.empty() || receivedPassword.empty())
					return crow::response(400);

				if (!db.PlayerIsInDatabase(receivedUsername, receivedPassword, receivedEmail))
				{
					if (db.AddPlayerToDatabase(receivedUsername, receivedEmail, receivedPassword))
						return crow::response(201);
				}
				else return crow::response(406);

			});

	CROW_ROUTE(m_app, "/verifyuser")
		.methods(crow::HTTPMethod::GET)([&db](const crow::request& req)
			{
				std::string receivedUsername = req.url_params.get("username");
				std::string receivedPassword = req.url_params.get("password");
				std::string receivedEmail = req.url_params.get("email");

				if (receivedPassword.empty() || receivedUsername.empty() || receivedEmail.empty())
					return crow::response(400);

				if (db.PlayerIsInDatabase(receivedUsername, receivedPassword, receivedEmail))
					return crow::response(302);

				return crow::response(404);
			});

	CROW_ROUTE(m_app, "/login")
		.methods(crow::HTTPMethod::GET)([&db, &lobbies, &game](const crow::request& req)
			{
				//IF USER ALREADY LOGGED IN, BUT NOT JOINED OR CREATED LOBBY, THEN IT WILL STILL LET IT PASS
				//CAN BE FIXED BY HAVING A VECTOR OF LOGGED IN PLAYER USERNAMES?
				std::string receivedUsername = req.url_params.get("username");
				std::string receivedPassword = req.url_params.get("password");

				if (receivedPassword.empty() || receivedUsername.empty())
					return crow::response(400);

				if (!db.PlayerIsInDatabase(receivedUsername, receivedPassword))
					return crow::response(404);

				//CHECK IF USERNAME IS IN LOBBY OR GAME
				if (!lobbies.empty()) 
				{
					auto foundLobby = GetLobbyWithPlayer(lobbies, receivedUsername);
					if (foundLobby->get())
						return crow::response(409);
				}
				if (game)
				{
					if (game->IsPlayerInGame(receivedUsername))
						return crow::response(409);
				}
				return crow::response(202);
			});

	CROW_ROUTE(m_app, "/deleteuser")
		.methods(crow::HTTPMethod::GET)([&db](const crow::request& req)
			{
				std::string receivedUsername = req.url_params.get("username");

				if (receivedUsername.empty())
					return crow::response(400);

				else {
					db.DeletePlayerFromDatabase(receivedUsername);
					return crow::response(202);
				}
				return crow::response(404);
			});

	CROW_ROUTE(m_app, "/createlobby")
		.methods(crow::HTTPMethod::GET)([&lobbies](const crow::request& req)
			{
				//CREATELOBBY EXPECTS THAT LOGIN BLOCKS ALREADY LOGGED IN USERS
				//CHECK DATA
				std::string receivedUsername = req.url_params.get("username");
				if (receivedUsername.empty())
					return crow::json::wvalue{ "ERROR: NO USERNAME"};
				if (!lobbies.empty())
				{
					//IF PLAYER IS ALREADY IN A LOBBY
					auto foundLobby = GetLobbyWithPlayer(lobbies, receivedUsername);
					if (foundLobby->get())
						return crow::json::wvalue{ "ERROR: USER ALREADY IN A LOBBY"};
				}
				//CREATE NEW LOBBY AND ADD PLAYER TO LOBBY
				std::unique_ptr<Lobby> lobby = std::make_unique<Lobby>();
				std::unique_ptr<Player> player = std::make_unique<Player>(receivedUsername);
				lobby->AddPlayer(player);
				//GET LOBBY CODE TO BE SENT
				std::string lobbyCode{ lobby->GetLobbyCode() };
				//ADD LOBBY TO LOBBIES VECTOR
				lobbies.emplace_back(std::move(lobby));
				//RETURN LOBBY CODE
				return crow::json::wvalue{ lobbyCode };
			});

	CROW_ROUTE(m_app, "/joinlobby")
		.methods(crow::HTTPMethod::GET)([&lobbies](const crow::request& req)
			{
				std::string receivedLobbyCode = req.url_params.get("lobbycode");
				std::string receivedUsername = req.url_params.get("username");

				//CHECK DATA
				if (receivedLobbyCode.empty() || receivedUsername.empty())
					return crow::response(400);

				//CHECK IF THERE IS A LOBBY
				if (lobbies.empty())
					return crow::response(404);

				//CHECK IF THERE IS A LOBBY WITH LOBBYCODE
				auto foundLobby = GetLobbyWithCode(lobbies, receivedLobbyCode);
				if (!foundLobby->get())
					return crow::response(400);
				try 
				{
					//TRY ADDING PLAYER
					std::unique_ptr<Player> player = std::make_unique<Player>(receivedUsername);
					foundLobby->get()->AddPlayer(player);
					return crow::response(200);
				}
				catch (...)
				{
					//THERE IS ALREADY A PLAYER WITH THAT USERNAME IN LOBBY WITH LOBBYCODE
					return crow::response(409);
				}
			});

	CROW_ROUTE(m_app, "/getlobbystatus")
		.methods(crow::HTTPMethod::GET)([&lobbies](const crow::request& req)
			{
				std::string receivedLobbyCode = req.url_params.get("lobbycode");

				//CHECK DATA
				if (receivedLobbyCode.empty())
					return crow::json::wvalue{ "ERROR: NO LOBBYCODE IN PARAMETERS"};

				//CHECK IF THERE IS A LOBBY
				if (lobbies.empty())
					return crow::json::wvalue{ "ERROR: NO LOBBY"};

				//CHECK IF THERE IS A LOBBY WITH LOBBYCODE
				auto foundLobby = GetLobbyWithCode(lobbies, receivedLobbyCode);
				if (!foundLobby->get())
					return crow::json::wvalue{ "ERROR: NO LOBBY WITH LOBBYCODE"};

				return crow::json::wvalue{ foundLobby->get()->GetStatusOfLobby() };
			});
	
	//CROW_ROUTE(m_app, "/getlobbycode")
	//	.methods(crow::HTTPMethod::GET)([&lobby](const crow::request& req)
	//		{
	//			return crow::json::wvalue{ lobby->GetLobbyCode()};
	//		});

	CROW_ROUTE(m_app, "/getusernamesfromlobby")
		.methods(crow::HTTPMethod::GET)([&lobbies](const crow::request& req)
			{
				//CHECK DATA
				std::string receivedLobbyCode = req.url_params.get("lobbycode");
				if (receivedLobbyCode.empty())
					return crow::json::wvalue{ "ERROR: NO LOBBY CODE IN PARAMETERS" };
				//CHECK IF THERE EXISTS A LOBBY
				if(lobbies.empty())
					return crow::json::wvalue{ "ERROR: NO LOBBY" };
				//FIND LOBBY WITH LOBBYCODE 
				auto foundLobby = GetLobbyWithCode(lobbies, receivedLobbyCode);
				if (!foundLobby->get())
					return crow::json::wvalue{ "ERROR: NO LOBBY WITH CODE" };
				//GET DATA OF PLAYERS
				std::vector<crow::json::wvalue> gameData_json;
				auto playersUsername = foundLobby->get()->GetUsernamesOfPlayers();
				for (const auto& username : playersUsername)
				{
					gameData_json.push_back(crow::json::wvalue{
						{"username", username}
					});
				}
				return crow::json::wvalue{ gameData_json };
		});
	
	CROW_ROUTE(m_app, "/startgame")
		.methods(crow::HTTPMethod::GET)([&lobbies, &game,&db](const crow::request& req)
			{
				if (game)
					return crow::response(409);
				//CHECK DATA
				std::string receivedLobbyCode = req.url_params.get("lobbycode");
				std::string receivedDifficulty = req.url_params.get("difficulty");
				if (receivedLobbyCode.empty() || receivedDifficulty.empty())
					return crow::response(400);
				//CHECK DIFFICULTY
				int difficulty = std::stoi(receivedDifficulty);
				if (difficulty < 0 || difficulty>3)
					return crow::response(400);
				//CHECK IF THERE EXISTS A LOBBY
				if (lobbies.empty())
					return crow::response(404);
				//FIND LOBBY WITH LOBBYCODE 
				auto foundLobby = GetLobbyWithCode(lobbies, receivedLobbyCode);
				if (!foundLobby->get())
					return crow::response(404);

				//START GAME
				//SET DIFFICULTY OF GAME
				game = std::make_unique<Game>();
				game->ChangeDifficulty(difficulty);
				//MOVE PLAYERS FROM LOBBY TO GAME
				foundLobby->get()->MovePlayersToGame(*(game.get()));
				//START FIRST ROUND
				game->StartAnotherRound(db);
				return crow::response(200);
		});

	//ROUTES RELATED TO GAME
		
	CROW_ROUTE(m_app, "/getplayersdatafromgame")
		.methods(crow::HTTPMethod::GET)([&game]() {
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
				std::string receivedUsername = req.url_params.get("username");
				std::string receivedMessage = req.url_params.get("message");
				if (receivedUsername.empty() || receivedMessage.empty())
					return crow::response(400);
				//CHECK IF THERE IS A GAME
				if (!game)
					return crow::response(404);
				//ADD MESSAGES TO CHAT
				//game->AddMessageToChat(std::string{}, std::string{ "Test de la server." });
				game->AddMessageToChat(receivedMessage, receivedUsername);
				return crow::response(200);
			});

	CROW_ROUTE(m_app, "/getchat")
		.methods(crow::HTTPMethod::GET)([&game](const crow::request& req) {
				//CHECK DATA
				std::string receivedUsername = req.url_params.get("username");
				if (receivedUsername.empty())
					return crow::json::wvalue{ "ERROR: NO USERNAME IN PARAMETERS" };
				if(!game)
					return crow::json::wvalue{ "ERROR: NO GAME IN PROCESS" };

				//GET CHAT
				std::vector<crow::json::wvalue> gameData_json;
				auto messages = game->GetChat(receivedUsername);
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
				return crow::json::wvalue{ game->GetRoundNumber()};
			});

	CROW_ROUTE(m_app, "/gettimer")
		.methods(crow::HTTPMethod::GET)([&game](const crow::request& req)
			{
				return crow::json::wvalue{ game->GetTimer() };
			});
	
	CROW_ROUTE(m_app, "/getboard")
		.methods(crow::HTTPMethod::GET)([&game](const crow::request& req)
			{
				auto board = game->GetBoard();
				std::string boardToSend;
				for (size_t i = 0; i < board.size(); ++i) 
				{
					boardToSend.push_back(char(board[i] + '0'));
				}
				return crow::json::wvalue{ {"board", boardToSend} };
			});
	
	CROW_ROUTE(m_app, "/sendboard")
		.methods(crow::HTTPMethod::PUT)([&game](const crow::request& req)
			{
				std::string stringBoard = req.url_params.get("board");
				if (stringBoard.size() != Game::kSize)
					return crow::response(400);
				std::array<uint16_t, Game::kSize> newBoard;
				for (size_t i = 0; i < stringBoard.size(); ++i)
				{
					newBoard[i] = static_cast<uint16_t>(stringBoard[i]-'0');
				}
				game->UpdateBoard(newBoard);
				return crow::response(200);
			});
	CROW_ROUTE(m_app, "/getword")
		.methods(crow::HTTPMethod::Get)([&game](const crow::request& req)
			{
				std::string receivedUsername = req.url_params.get("username");
				if (receivedUsername.empty())
					return crow::json::wvalue{ "ERROR: NO USERNAME IN PARAMETERS" };
				//CHECK IF THERE IS A GAME
				if (!game)
					return crow::json::wvalue{ "ERROR: NO GAME IN PROGRESS." };
				if (receivedUsername == game->GetPainterUsername())
				{
					return crow::json::wvalue{ {"Word", game->GetHiddenWord()}};
				}
				else
				{
					return crow::json::wvalue{ {"Word", game->GetShownWord()} };
				}
			});
}

crow::SimpleApp& Routing::GetApp()
{
	return m_app;
}

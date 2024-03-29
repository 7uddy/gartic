#include <crow.h>
#include "../../Gartic/includes/garticDatabase.h"
#include "../../Gartic/includes/routing.h"

import lobby;

using namespace gartic;

int main()
{
	GarticDatabase storage;
	if (!storage.Initialize())
	{
		std::cout << "Faild to initialize the database!";
		return -1;
	}
	std::unique_ptr<Game> game;
	std::unordered_map<std::string, std::unique_ptr<Lobby>> lobbies;
	std::unordered_set<std::string> loggedInPlayers;
	Routing r;
	r.Run(storage, game, lobbies, loggedInPlayers);
	r.GetApp().port(18080).multithreaded().run();
	return 0;
}
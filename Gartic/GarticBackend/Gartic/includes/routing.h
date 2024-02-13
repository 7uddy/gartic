#pragma once

#include <crow.h>
#include "../../Gartic/includes/garticDatabase.h"

import lobby;

import <unordered_set>;

namespace gartic
{
	class Routing
	{
	public:
		void Run(GarticDatabase& storage, std::unique_ptr<Game>&, std::unordered_map<std::string, std::unique_ptr<Lobby>>&, std::unordered_set<std::string>&);
		crow::SimpleApp& GetApp();

	private:
		crow::SimpleApp m_app;
	};
}
#pragma once

#include <crow.h>
#include "../../Gartic/includes/garticDatabase.h"

import lobby;

namespace gartic
{
	class Routing
	{
	public:
		void Run(GarticDatabase& storage, std::unique_ptr<Game>&, std::vector<std::unique_ptr<Lobby>>&);
		crow::SimpleApp& GetApp();

	private:
		crow::SimpleApp m_app;
	};
}
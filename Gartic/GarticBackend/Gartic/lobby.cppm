module;
export module lobby;

import player;
import <cstdint>;
import <string>;
import <vector>;
import <iostream>;

namespace gartic
{
	export class Lobby
	{
	public:
		Lobby() = default;
		void addPlayer(Player&& player) noexcept;

		//ERROR IN std::find FUNCTION
		void removePlayer(const std::string& username);
		bool isInLobby(const std::string& username) const;
		//

		void clearLobby() noexcept;

		uint16_t getNumberOfPlayers() const noexcept;
		const std::string& getLobbyCode() const noexcept;
		std::vector<Player>&& getPlayersToMove();
	private:
		std::vector<Player> m_players;
		std::string m_lobbyCode;
	};
}
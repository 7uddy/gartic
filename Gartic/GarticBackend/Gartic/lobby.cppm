module;
export module lobby;

import game;
import <cstdint>;
import <string>;
import <vector>;
import <iostream>;
import <random>;

namespace gartic
{
	export class Lobby
	{
	public:
		enum class Status : uint8_t
		{
			WaitingForPlayers,
			Launched,
			Terminated
		};
	public:
		Lobby();
		void addPlayer(Player&& player) noexcept;
		void removePlayer(const std::string& username);
		bool isInLobby(const std::string& username) const;

		void clearLobby() noexcept;

		uint16_t getNumberOfPlayers() const noexcept;
		const std::string& getLobbyCode() const noexcept;
		const Status& getStatusOfLobby() const noexcept;

		void StartGame(Game& game);
		bool CheckLobbyCode(const std::string&) const;

	private:
		void GenerateLobbyCode();
		int GetRandomDigit(int maxim=57) const;

	private:
		static const char k_lengthOfLobbyCode = 4;
	private:
		std::vector<Player> m_players;
		std::string m_lobbyCode;
		Status m_lobbyStatus;
	};
}
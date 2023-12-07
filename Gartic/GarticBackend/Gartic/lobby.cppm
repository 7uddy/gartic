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

		//FOR GUI
		uint16_t getNumberOfPlayers() const noexcept;
		int getStatusOfLobby() const noexcept;

		const std::string& getLobbyCode() const noexcept;
		bool CheckLobbyCode(const std::string&) const;

		void StartGame(Game& game);
		void CloseLobby(Game& game);
		//

	private:
		void GenerateLobbyCode();
		int GetRandomDigit(int) const;
		int ConvertLobbyStatusToInteger() const noexcept;

		void clearLobby() noexcept;

	private:
		static const char k_lengthOfLobbyCode = 4;
	private:
		std::vector<Player> m_players;
		std::string m_lobbyCode;
		Status m_lobbyStatus;
	};
}
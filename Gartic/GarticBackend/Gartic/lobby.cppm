module;
export module lobby;

export import game;

//import <iostream>;
//import <string>;
//import <cstdint>;
//import <unordered_map>;
//import <memory>;
import <random>;

namespace gartic
{
	export class Lobby
	{
	public:
		enum class Status : uint8_t
		{
			WaitingForPlayers,
			Launched
		};
	public:
		Lobby();

		//Functions related to end game
		void AddRequestForEnd() noexcept;
		bool TimeToDeleteLobby() const noexcept;


		void AddPlayer(std::unique_ptr<Player>&);
		void RemovePlayer(const std::string& username);
		bool IsInLobby(const std::string& username) const;

		//FOR GUI
		uint16_t GetNumberOfPlayers() const noexcept;
		std::vector<std::string> GetUsernamesOfPlayers() const noexcept;
		int GetStatusOfLobby() const noexcept;

		const std::string& GetLobbyCode() const noexcept;
		bool CheckLobbyCode(const std::string&) const;

		//FOR TEST
		void PrintPlayers() const noexcept;
		void MovePlayersToGame(Game& game);

		int ConvertStatusToInteger(const Status&) const noexcept;
	private:
		void GenerateLobbyCode() noexcept;
		int GetRandomDigit(const std::pair<int, int>&) const;
		void ClearLobby() noexcept;

	private:
		static const char k_lengthOfLobbyCode = 5;
	private:
		std::unordered_map<std::string, std::unique_ptr<Player>> m_players;
		std::string m_lobbyCode;
		Status m_lobbyStatus;
		uint16_t m_requestsToDeleteLobby;
		uint16_t m_numberOfPlayers;
	};
}
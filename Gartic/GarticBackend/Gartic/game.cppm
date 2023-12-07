module;

export module game;


export import round;
export import <string>;
export import <iostream>;
export import <vector>;
export import <optional>;
export import <cstdint>;

namespace gartic
{
	export class Game
	{
	public:
		/*-------Enums-------*/
		enum class Status : uint8_t
		{
			Inactive,
			Active,
			Finished
		};

		/*-------Game variables related functions-------*/
		Game() = default;


		const uint16_t& getGameID() const noexcept;

		void setPlayers(std::vector<Player>&&) noexcept;
		void addPlayerToGame(Player&&);
		void deletePlayerFromGameWithID(const uint16_t&);

		//void changeGameStatus() noexcept;
		void changeDifficulty(int) noexcept;

		uint16_t GetDifficulty() const noexcept;

		void startAnotherRound() noexcept;
		void showAllPlayers() const noexcept; //for test
		bool IsPlayerInGame(const Player& newPlayer) const noexcept;
		 
		//FOR GUI
		uint16_t getTimer() const noexcept;
		const std::vector<Player>& getPlayers() const noexcept;
		void AddMessageToChat(const uint16_t&, const std::string&) noexcept;
		void ClearChat() noexcept;
		std::string GetChat(const uint16_t&) const noexcept;
	 private:
		std::vector<Player> m_players;
		uint16_t m_gameID;
		Status m_gameState;
		Round m_round;
		std::vector<std::pair<std::optional<uint16_t>, std::string>> m_chat;
	};
}
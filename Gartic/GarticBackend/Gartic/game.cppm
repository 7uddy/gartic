module;

export module game;


export import round;
import <string>;
import <iostream>;
import <vector>;

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

		void sortPlayersByCurrentScore() noexcept;

		void setPlayers(std::vector<Player>&&) noexcept;
		void addPlayerToGame(Player&&);
		void deletePlayerFromGameWithID(const uint16_t&);

		void changeGameStatus() noexcept;
		void changeDifficulty(const Round::Difficulty&) noexcept;

		void startAnotherRound() noexcept;
		void showAllPlayers() const noexcept;

	 private:
		std::vector<Player> m_players;
		uint16_t m_gameID;
		Status m_gameState;
		Round::Difficulty m_difficulty;
		Round m_round;

	};
}
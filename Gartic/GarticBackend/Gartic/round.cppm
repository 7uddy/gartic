module;
export module round;
export import player;

import <chrono>;
import <iostream>;
import <string>;

namespace gartic
{
	export class Round
	{
	public:
		using Time = std::chrono::time_point<std::chrono::steady_clock>;

		enum class Difficulty : uint8_t
		{
			Easy,
			Medium,
			Hard
		};

	public:
		Round() = default;
		Round(Difficulty, std::vector<Player>*);
		//FUNCTIONS FOR ROUND AND SCORE 
		void startRound() noexcept;
		void endRound() noexcept;

		bool isWordCorrectAndAddUserGuessTime(const uint16_t& id, const std::string& guess) noexcept;
		std::string getWord(const uint16_t& id) const noexcept;

		uint16_t getSecondsFromStart() const noexcept;
		//FOR TEST
		void showAllPlayers() const noexcept;

	private:
		void addPlayerGuessTime(const uint16_t& id);
		void choosePainter() noexcept;
		void updateScoreForPlayer(Player*, const uint16_t&) noexcept;

	private:
		static Player* m_painter;
		static const uint16_t k_numberOfRounds = 4;
		static const uint16_t kWordNumber = 499;


	private:
		std::vector<Player>* m_players;
		Difficulty m_difficulty;
		uint16_t m_miniRoundNumber;
		Time m_startRoundTime;
		std::vector<std::pair<Player*, uint16_t>> m_guessTimes;


		//Variables related to word
		std::string m_hiddenWord;
		std::string m_shownWord;
		uint8_t m_lettersToShow;
	};
}
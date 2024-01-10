module;
export module round;
export import word;
export import player;

import <chrono>;
//import <iostream>;
//import <string>;
export import <unordered_map>;
export import <cstdint>;
export import <random>;

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

		//FUNCTIONS FOR ROUND AND SCORE 
		bool StartRound(const Word& word);
		void EndRound() noexcept;

		uint16_t GetCurrentRound() const noexcept;
		uint16_t GetSecondsFromStart() const noexcept;
		void SetDifficulty(int);
		uint16_t GetDifficulty() const noexcept;
		const std::string& GetPainterUsername() const noexcept;
		const std::string& GetHiddenWord() const noexcept;
		const std::string& GetShownWord() const noexcept;
		const int GetTimeForHint() const noexcept;
		const int GetNumberOfHints() const noexcept;
		const bool WasHintShown(const int& index) const noexcept;
		bool IsHiddenWord(const std::string& receivedWord);
		const std::vector<std::shared_ptr<Player>> GetPlayers() const noexcept;

		//FOR TEST
		void ShowAllPlayers() const noexcept;
		void ShowAllPlayerGuessTimes() const noexcept;
		void AddPlayer(std::shared_ptr<Player> player);

		void AddPlayerGuessTime(const std::string&);
		void GetNextHint() noexcept;
	private:
		void ChoosePainter() noexcept;
		void CalculateScoreForPlayers() noexcept;
		void UpdateScoreForPlayer(std::shared_ptr<Player>) noexcept;
		uint16_t DifficultyToInteger(const Difficulty&) const;
		Difficulty IntegerToDifficulty(int) const;
		int GetRandomIndex() const noexcept;

	private:
		static std::shared_ptr<Player> m_painter;
		static const uint16_t k_numberOfRounds = 4;
		static const uint8_t k_roundSeconds = 60;

	private:
		std::vector<std::shared_ptr<Player>> m_players;
		Difficulty m_difficulty;
		bool m_difficultyIsAscending;
		uint16_t m_miniRoundNumber;
		Time m_startRoundTime;
		std::unordered_map<std::string, uint16_t> m_guessTimes;


		//Variables related to word
		std::string m_shownWord;
		std::vector<bool> m_lettersToShow;
		std::string m_hiddenWord;
		int m_timeForHint;

	};
}
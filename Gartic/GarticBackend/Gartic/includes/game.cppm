module;

#include "garticDatabase.h"
export module game;
import <vector>;

export import word;
export import round;

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
			Finished,
			Transitioning
		};

		using Coordinate = std::pair<int, int>;
		/*-------Game variables related functions-------*/
		Game() = default;
		Game(int gameID);
		~Game() = default;

		//Methods related to game status
		void AddRequestForEnd() noexcept;
		bool TimeToEndGame() const noexcept;
		bool AllPlayersGuessed() const noexcept;
		void SetStatusOfGame(const Status& newStatus);
		void StartAnotherRound(GarticDatabase& storage) noexcept;
		void SaveScoresInDatabase(GarticDatabase& storage) const noexcept;
		//

		void AddPlayerToGame(std::unique_ptr<Player>);
		void RemovePlayer(std::string_view);

		bool AddMessageToChat(std::string&& message, const std::string& username = "") noexcept;
		void ChangeDifficulty(int);

		void IsTimeForHint();

		bool IsPlayerInGame(std::string_view) const noexcept;

		//FOR GUI
		const int& GetGameStatus() const noexcept;
		const int& GetGameID() const noexcept;
		uint16_t GetTimer() const noexcept;
		uint16_t GetDifficulty() const noexcept;
		uint16_t GetRoundNumber() const noexcept;
		const std::vector<Coordinate>& GetBoard() const noexcept;
		void UpdateBoard(std::vector<Coordinate>&&);
		std::vector<std::shared_ptr<Player>> GetPlayers() noexcept;
		std::vector<std::string> GetChat(std::string_view) const noexcept;
		const std::string& GetPainterUsername() const noexcept;
		const std::string& GetHiddenWord() const noexcept;
		const std::string& GetShownWord() const noexcept;
		//

		void ClearChat() noexcept;
		static int ConvertStatusToInteger(const Status&);
	private:

	private:
		std::unordered_map<std::string, std::shared_ptr<Player>> m_players;
		int m_gameID;
		Status m_gameState;
		Round m_round;
		std::vector<std::pair<std::optional<std::string>, std::string>> m_chat;
		std::vector<Coordinate> m_board;
		std::vector<Word> pastWords;
		uint16_t m_requestsToEndGame;
	};
}
module;

#include "garticDatabase.h"
export module game;

import <array>;

export import round;

//import <iostream>;
//import <string>;
//import <string_view>;
//import <optional>;
//export import <memory>;
//import <cstdint>;
//import <unordered_map>;

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

		static const size_t kNumberOfLines{ 80 };
		static const size_t kNumberOfColumns{ 80 };
		static const size_t kSize{ kNumberOfColumns * kNumberOfLines };

		/*-------Game variables related functions-------*/
		Game() = default;
		~Game() = default;


		void StartAnotherRound(GarticDatabase& storage) noexcept;

		void AddPlayerToGame(std::unique_ptr<Player>);
		void UpdateBoard(const std::array<uint16_t, kSize>&);
		void RemovePlayer(std::string_view);

		void AddMessageToChat(std::string_view, std::string_view) noexcept;
		void ChangeDifficulty(int) noexcept;

		//For Test
		void ShowAllPlayers() const noexcept; //for test
		bool IsPlayerInGame(std::string_view) const noexcept;

		//FOR GUI
		const std::string& GetGameID() const noexcept;
		uint16_t GetTimer() const noexcept;
		uint16_t GetDifficulty() const noexcept;
		uint16_t GetRoundNumber() const noexcept;
		std::array<uint16_t, kSize> GetBoard() const noexcept;
		std::vector<std::shared_ptr<Player>> GetPlayers() const noexcept;
		std::vector<std::string> GetChat(std::string_view) const noexcept;
		//

		void ClearChat() noexcept;

	private:
		std::unordered_map<std::string, std::shared_ptr<Player>> m_players;
		std::string m_gameID;
		Status m_gameState;
		Round m_round;
		std::vector<std::pair<std::optional<std::string>, std::string>> m_chat;
		std::array<uint16_t, kSize> m_board;
	};
}
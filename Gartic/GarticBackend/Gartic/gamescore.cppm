module;

export module gamescore;

import <string>;

namespace gartic
{
	export class GameScore
	{
	public:
		GameScore()=default;
		GameScore(int gameID, const std::string& username, float score);

		void SetGameId(const int& gameID) noexcept;
		void SetUsername(const std::string& username) noexcept;
		void SetScore(const float& score) noexcept;

		const int& GetGameId() const noexcept;
		const std::string& GetUsername() const noexcept;
		const float& GetScore() const noexcept;


	private:
		int m_gameID;
		std::string m_username;
		float m_score;
	};
}
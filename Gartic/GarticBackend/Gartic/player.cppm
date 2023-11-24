module;
export module player;

export import <string>;
export import <cstdint>;


namespace gartic
{
	export class Player
	{
	public:
		/*-------Constructors-------*/
		Player() = default;
		Player(const std::string& username, const std::string& password);
		Player(Player&& otherPlayer);

		Player& operator=(Player&& other) noexcept;

		/*-------Player variables related functions-------*/
		const uint16_t& getID() const noexcept;
		void setID(const uint16_t& id) noexcept;

		void setUsername(const std::string& username) noexcept;
		const std::string& getUsername() const noexcept;

		void setPassword(const std::string& password) noexcept;
		const std::string& getPassword() const noexcept;

		void setScoreTo(const float& score) noexcept;
		void addToScore(const float& score) noexcept;
		void resetScore() noexcept;
		const float& getScore() const noexcept;

		/*-------Operator overloading-------*/

		bool operator<(const Player&) noexcept;
		bool operator==(const Player&) const;
		bool operator!=(const Player&) const;

	private:
		uint16_t m_uniqueId;
		std::string m_username;
		std::string m_password;
		float m_score;
	};


}
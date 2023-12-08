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
		Player(std::string_view username,std::string_view password,std::string_view email,const int& uniqueId);
		Player(Player&& otherPlayer);

		Player& operator=(Player&& other) noexcept;

		/*-------Player variables related functions-------*/
		const int GetID() const noexcept;
		void SetID(const int id) noexcept;

		void SetUsername(std::string_view username) noexcept;
		std::string_view GetUsername() const noexcept;

		void SetEmail(std::string_view email) noexcept;
		std::string_view GetEmail() const noexcept;

		void SetPassword(std::string_view password) noexcept;
		std::string_view GetPassword() const noexcept;

		void SetScoreTo(const float& score) noexcept;
		void AddToScore(const float& score) noexcept;
		void ResetScore() noexcept;
		const float& GetScore() const noexcept;

		/*-------Operator overloading-------*/

		bool operator<(const Player&) noexcept;
		bool operator==(const Player&) const;
		bool operator!=(const Player&) const;

	private:
		int m_uniqueId;
		std::string m_username;
		std::string m_password;
		float m_score;
		std::string m_email;
	};


}
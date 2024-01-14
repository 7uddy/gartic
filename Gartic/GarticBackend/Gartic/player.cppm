module;
export module player;

export import <string>;
export import <iostream>;
import <fstream>;
import <type_traits>;

namespace gartic
{
	export class Player
	{
	public:
		/*-------Constructors-------*/
		Player() = default;
		Player(const std::string& username, const std::string& email, const std::string& password);
		Player(const std::string& username);
		Player(const Player&);
		Player(Player&& otherPlayer);

		Player& operator=(Player&& other) noexcept;

		//Setters
		void SetUsername(const std::string& username) noexcept;
		void SetPassword(const std::string& password) noexcept;
		void SetScoreTo(const float& score) noexcept;

		template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
		void AddToScore(const T& score) noexcept
		{
			m_score += score;
		}
		void SetEmail(const std::string& email) noexcept;

		//Getters
		const std::string& GetUsername() const noexcept;
		const std::string& GetPassword() const noexcept;
		float GetScore() const noexcept;
		const std::string& GetEmail() const noexcept;

		//Functions
		void ResetScore() noexcept;

		/*-------Operator overloading-------*/

		bool operator<(const Player&) noexcept;
		bool operator==(const Player&) const;
		bool operator!=(const Player&) const;

	private:
		std::string m_username;
		std::string m_password;
		std::string m_email;
		float m_score;
	};
	export std::ostream& operator<< (std::ostream& os, const Player& player);


}